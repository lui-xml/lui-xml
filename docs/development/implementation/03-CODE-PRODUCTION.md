# Code Production

**Purpose**: Guidelines for writing production code that satisfies OpenSpec specifications.

---

## Overview

This guide explains how to write production code that satisfies OpenSpec specifications. The key insight: **you're not just writing code, you're satisfying requirements.**

---

## Reading Specifications

### Before Writing Code

**Read the full spec** (don't skim):
```
specs/[capability]/spec.md
or
openspec/changes/[change-id]/specs/[capability]/spec.md
```

**What to Look For**:
1. **Requirements** (### Requirement: ...)
   - What MUST/SHALL the system do?
   - What are the constraints?

2. **Scenarios** (#### Scenario: ...)
   - What are the success cases?
   - What are the error cases?
   - What are the exact Given/When/Then conditions?

3. **References**
   - Specification sections (for context)
   - Roadmap phases (for scope)

### Example: Reading a Spec

**Specification**:
```markdown
### Requirement: Namespace Isolation
The system SHALL use `lui_` prefix for all public APIs and `luixml_` prefix
for internal widget bindings to prevent collision with LVGL symbols.

#### Scenario: Parser Initialization
- **GIVEN** Lui-XML library is loaded
- **WHEN** lui_xml_create() is called
- **THEN** an XML parser instance is created
- **AND** default widget parsers are registered (luixml_button, luixml_label)
- **AND** all symbols use lui_ or luixml_ namespace
- **AND** no symbols use lv_xml_ prefix
```

**Extracted Requirements**:
- MUST use lui_ prefix for public APIs
- MUST use luixml_ prefix for internal widgets
- MUST NOT use lv_xml_ prefix (forbidden)
- Default widgets: button, label, image

---

## Writing Testable Code

### Scenario-Driven Development

**Principle**: Every scenario becomes a test case.

**Process**:

1. **Write the Test First**
   ```c
   void test_parser_initialization() {
       // GIVEN
       assert(lui_xml_is_initialized() == false);
       
       // WHEN
       lui_xml_parser_t *parser = lui_xml_create();
       
       // THEN
       assert(parser != NULL);
       assert(lui_xml_widget_is_registered("button"));
       assert(lui_xml_widget_is_registered("label"));
       
       // Verify namespace
       assert(no_lv_xml_symbols_exist());
   }
   ```

2. **Implement to Pass the Test**
   ```c
   lui_xml_parser_t *lui_xml_create(void) {
       lui_xml_parser_t *parser = malloc(sizeof(lui_xml_parser_t));
       if (!parser) return NULL;
       
       // Register default widgets with luixml_ prefix
       luixml_register_button(parser);
       luixml_register_label(parser);
       luixml_register_image(parser);
       
       return parser;
   }
   ```

3. **Verify Constraints**
   ```c
   // In test
   assert(symbol_count("luixml_") == 3);  // All widgets registered
   assert(symbol_count("lv_xml_") == 0);  // No forbidden symbols
   ```

### Why This Works

- **Tests are the spec scenarios** - If tests pass, spec is satisfied
- **Constraints validated** - Explicit checks for namespace
- **Fail-fast** - Know immediately if spec violated

---

## Tracing Code to Requirements

### In Code Comments

```c
/**
 * XML Parser Creation
 *
 * Spec: xml-parser/spec.md
 * Requirement: Namespace Isolation
 * Scenario: Parser Initialization
 *
 * Creates XML parser with lui_xml namespace and registers
 * default widget parsers (luixml_button, luixml_label, luixml_image).
 *
 * Namespace Constraints:
 * - Public APIs: lui_ prefix
 * - Internal widgets: luixml_ prefix
 * - FORBIDDEN: lv_xml_ prefix (collision risk)
 *
 * @return Parser instance or NULL on failure
 */
lui_xml_parser_t *lui_xml_create(void);
```

### In Git Commits

```bash
git commit -m "feat(xml-parser): implement namespace isolation

Implements Namespace Isolation requirement from xml-parser/spec.md

Requirements satisfied:
- Public APIs use lui_ prefix
- Internal widgets use luixml_ prefix
- No lv_xml_ symbols (collision prevention)

Constraints:
- Namespace isolation ✓
- LVGL symbol collision prevention ✓

Scenarios:
- ✓ Parser Initialization (success)
- ✓ Symbol Collision Detection (error)

Refs: xml-parser/spec.md#requirement-1"
```

---

## Satisfying Constraints

### Namespace Constraints

**Spec Constraint**: "MUST use lui_ prefix for public APIs"

**Implementation**:
```c
// Public API - lui_ prefix
lui_xml_parser_t *lui_xml_create(void);
lui_obj_t *lui_xml_load(lui_xml_parser_t *, const char *);
```

**Validation**:
```bash
# Check for proper namespace
grep -r "^lui_" src/ --include="*.c" --include="*.h"

# Check for forbidden namespace
grep -r "lv_xml_" src/ --include="*.c" --include="*.h"
# If found: FAIL - must rename to lui_xml_ or luixml_
```

### Build System Constraints

**Spec Constraint**: "MUST detect existing LVGL target"

**Implementation**:
```cmake
# CMakeLists.txt
if(TARGET lvgl)
    message(STATUS "Lui-XML: Integrating with existing LVGL target")
else()
    message(FATAL_ERROR "Lui-XML requires LVGL target. Include LVGL first.")
endif()
```

**Test**:
```python
def test_lvgl_detection():
    # Setup: CMake project without LVGL
    # When
    result = configure_lui_xml()
    # Then
    assert result.error == "LVGL target not found"
```

### Legal Constraints

**Spec Constraint**: "MUST preserve git authorship"

**Implementation**:
```bash
# During Phase 1 extraction
git filter-repo ...path-rename src/xml/:src/ ...

# Verify authorship preserved
git log --format="%an <%ae>" src/lui_xml_parser.c | head -10
# Should show original LVGL authors, NOT your name
```

---

## Error Handling

### Spec-Driven Error Handling

**Spec Scenario**:
```markdown
#### Scenario: Invalid XML Syntax
- **GIVEN** XML string contains malformed syntax
- **WHEN** lui_xml_load() is called
- **THEN** the parser returns LUI_XML_ERROR_SYNTAX
- **AND** error position is reported
```

**Implementation**:
```c
lv_obj_t *lui_xml_load(lui_xml_parser_t *parser, const char *xml_string) {
    xml_node_t *root = xml_parse_string(xml_string);
    
    if (xml_has_syntax_error(root)) {
        parser->last_error = LUI_XML_ERROR_SYNTAX;
        parser->error_line = xml_get_error_line(root);
        parser->error_col = xml_get_error_column(root);
        return NULL;
    }
    
    return build_lvgl_object_tree(root);
}
```

**Test**:
```c
void test_invalid_xml_syntax() {
    const char *invalid_xml = "<button><label>Text</button>";  // Missing </label>
    
    lv_obj_t *result = lui_xml_load(parser, invalid_xml);
    
    assert(result == NULL);
    assert(parser->last_error == LUI_XML_ERROR_SYNTAX);
    assert(parser->error_line == 1);
}
```

---

## Code Organization

### Module Structure

Organize code by requirement, not by technical layer:

**Good** (requirement-focused):
```
src/
├── lui_xml_parser.c/h         # Requirement 1: XML Parser
├── luixml_button.c/h           # Requirement 2: Button Widget
├── luixml_label.c/h            # Requirement 3: Label Widget
└── luixml_image.c/h            # Requirement 4: Image Widget
```

**Less Good** (layer-focused):
```
src/
├── parser.c                     # Mixes parser and widgets
├── widgets.c                    # Mixes all widgets together
```

### File Naming

Match spec requirement names:

| Requirement | File Name |
|-------------|-----------|
| XML Parser | `lui_xml_parser.c` |
| Button Widget | `luixml_button.c` |
| Label Widget | `luixml_label.c` |
| Build Integration | `cmake_integration.c` |

---

## Documentation in Code

### Function Documentation

```c
/**
 * Load LVGL UI from XML markup
 *
 * Spec: xml-parser/spec.md
 * Requirement: XML Loading
 * Scenario: Load Valid XML
 *
 * This function parses XML markup and creates corresponding LVGL objects.
 * The XML format supports button, label, and image widgets.
 *
 * Namespace Constraints:
 * - Widget parsers use luixml_ prefix
 * - No lv_xml_ symbols (forbidden)
 *
 * @param parser XML parser instance
 * @param xml_string XML markup string (null-terminated)
 *
 * @return LVGL object root, or NULL on error
 *
 * Errors:
 * - LUI_XML_ERROR_SYNTAX: XML malformed
 * - LUI_XML_ERROR_UNSUPPORTED_WIDGET: Widget type not supported
 *
 * Example:
 * ```c
 * lui_xml_parser_t *parser = lui_xml_create();
 * const char *xml = "<label>Text</label>";
 * lv_obj_t *screen = lui_xml_load(parser, xml);
 * ```
 */
lv_obj_t *lui_xml_load(lui_xml_parser_t *parser, const char *xml_string);
```

---

## Anti-Patterns

### Anti-Pattern 1: Implementing Without Reading Spec

**Wrong**:
```
"I need to implement XML parsing. Let me start coding."
```

**Correct**:
```
"I need to implement the XML Parser requirement from xml-parser/spec.md.
Let me read the spec first to understand what's required."
```

### Anti-Pattern 2: Ignoring Namespace Constraints

**Wrong**:
```c
lv_xml_parser_t *lv_xml_create(void);  // Forbidden prefix!
```

**Correct**:
```c
lui_xml_parser_t *lui_xml_create(void);  // Correct prefix
```

### Anti-Pattern 3: Adding Extra Features

**Wrong**:
```c
// While I'm here, let me add JSON support
load_from_json(json_string);  // NOT IN SPEC
```

**Correct**:
```c
// Only what spec requires
lui_xml_load(parser, xml_string);
```

---

## Quick Reference

**The Code Production Checklist**:
- [ ] Read and understand the full spec
- [ ] Extract all requirements and constraints
- [ ] Write tests for each scenario
- [ ] Implement to pass tests
- [ ] Verify namespace constraints (lui_/luixml_ only)
- [ ] Verify build system integration
- [ ] Trace code to requirements in comments
- [ ] Handle all error scenarios

**The Golden Rule**:

> **"Code is correct when it satisfies the specification. Tests are correct when they match the scenarios."**

---

**Next**: Read `04-VALIDATION.md` to learn about validating your implementation against specifications.
