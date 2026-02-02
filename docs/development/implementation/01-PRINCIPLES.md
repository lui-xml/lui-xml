# Core Principles of Implementation

**Purpose**: The foundational principles that guide all implementation work from OpenSpec specifications.

**Status**: NON-NEGOTIABLE - These principles must be followed for all implementation work.

---

## 🚨 CRITICAL: Read This First

**BEFORE implementing anything, read `00-ANTI-PATTERNS-TO-AVOID.md`**

That document contains critical anti-patterns that will cause immediate rejection:
- **NEVER use TODOs in production code**
- **NEVER use placeholder implementations**
- **NEVER use stub functions that don't work**
- **NEVER use mock implementations in production**
- **NEVER violate namespace isolation (lv_xml_ is FORBIDDEN)**

The anti-patterns document explains why these are unacceptable and shows the correct approach.

**Summary**: Do it right the first time. It's actually easier than using placeholders and then having to redo it.

---

## The Core Principle

**Focus on SPECIFICATION SATISFACTION, not code completion metrics.**

### What This Means

**Wrong Mindset** (led to failure before):
- "I implemented all the functions"
- "All unit tests are passing"
- "Code compiles without warnings"
- "I can mark this complete"

**Right Mindset** (leads to success):
- "The system satisfies all specified requirements"
- "All scenarios pass (happy path and edge cases)"
- "The system produces correct output in production"
- "Success criteria from specs are met"

### Why This Matters

From real-world experience:
- Teams have completed 100% of implementation tasks
- All tests passed in isolation
- Code coverage was 100%
- **The system didn't satisfy the actual requirements**

**Task completion metrics can be deceptive. Specification satisfaction matters.**

---

## Principle 1: Specification First, Implementation Second

### The Principle

**Never write implementation code until you understand the specification.**

### How to Apply

**Wrong Approach**:
1. Read tasks.md (implementation task list)
2. Start implementing immediately
3. Create tests with mock data
4. Realize you misunderstood the requirement

**Right Approach**:
1. Read the full spec (spec.md)
2. Read the design doc (design.md) if it exists
3. Understand every requirement and scenario
4. Plan the implementation
5. Write code that satisfies the specification

### Validation Criteria

✅ **Correct**: You can explain each requirement in your own words
✅ **Correct**: You can trace your code to specific requirements
✅ **Correct**: You understand the success and error scenarios
❌ **Incorrect**: "I read the spec" (but can't explain it)
❌ **Incorrect**: "Tests pass" (but don't match spec scenarios)

---

## Principle 2: Scenario-Driven Development

### The Principle

**Every scenario in the specification is a test case. Your implementation must make all scenarios pass.**

### How to Apply

For each requirement:
1. List all scenarios (success and error)
2. Write test cases for each scenario
3. Implement code to make tests pass
4. Verify production behavior matches scenarios

### Example

**Specification Scenario**:
```markdown
#### Scenario: XML Parser Initialization
- **GIVEN** Lui-XML library is loaded
- **WHEN** lui_xml_create() is called
- **THEN** an XML parser instance is created
- **AND** default widget parsers are registered
- **AND** all symbols use lui_ or luixml_ namespace prefixes
```

**Test Case**:
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
}
```

**Implementation**:
- Write lui_xml_create() that initializes parser
- Write lui_xml_widget_register() for default widgets
- Ensure namespace compliance (lui_/luixml_ only)

### Validation Criteria

✅ **Correct**: Every scenario has a corresponding test
✅ **Correct**: All tests pass
❌ **Incorrect**: "Unit tests pass" (but don't match spec scenarios)

---

## Principle 3: Traceability is Mandatory

### The Principle

**Every line of production code should trace back to a requirement.**

### How to Apply

**In Code Comments**:
```c
/**
 * XML Parser Initialization
 * Spec: xml-parser/spec.md
 * Requirement: Namespace Isolation
 * Scenario: Parser Initialization
 *
 * Initializes XML parser with lui_xml namespace and registers
 * default widget parsers (luixml_button, luixml_label, luixml_image).
 *
 * Constraints:
 * - MUST use lui_ prefix for public APIs
 * - MUST use luixml_ prefix for internal widgets
 * - MUST NOT use lv_xml_ prefix (forbidden)
 *
 * @param void
 * @return Parser instance or NULL on failure
 */
lui_xml_parser_t *lui_xml_create(void);
```

**In Git Commits**:
```
feat(xml-parser): implement namespace isolation

Implements Namespace Isolation requirement from xml-parser/spec.md

- All public APIs use lui_ prefix
- All internal widgets use luixml_ prefix
- No lv_xml_ symbols (collision prevention)

Constraints:
- Namespace isolation ✓
- LVGL symbol collision prevention ✓

Refs: xml-parser/spec.md#requirement-1
```

### Validation Criteria

✅ **Correct**: Code comments reference spec requirements
✅ **Correct**: Git commits reference spec requirements
✅ **Correct**: Can explain why any line of code exists
❌ **Incorrect**: "This is good code" (but can't trace to requirement)

---

## Principle 4: Constraints are Non-Negotiable

### The Principle

**All constraints in the specification must be satisfied. No exceptions.**

### Types of Constraints

**Namespace Constraints** (Lui-XML specific):
- Public APIs MUST use `lui_` prefix
- Internal widgets MUST use `luixml_` prefix
- MUST NOT use `lv_xml_` prefix (forbidden)

**Build System Constraints**:
- MUST detect existing LVGL target
- MUST fail gracefully if LVGL not found
- MUST support CMake 3.15+ and ESP-IDF

**Legal Constraints**:
- MUST preserve git authorship (PROVENANCE.md)
- MUST maintain MIT license with attribution
- MUST document code provenance

**Version Constraints**:
- Lui-XML v9.1.0-x requires LVGL v9.1.0
- MUST validate LVGL version compatibility

### How to Apply

**Before Implementation**:
- Read all constraints in the spec
- Read design.md for additional constraints
- Document how you'll satisfy each constraint

**During Implementation**:
- Verify namespace usage (lui_/luixml_ only)
- Check for lv_xml_ symbols (grep -r "lv_xml_")
- Test build system integration

**After Implementation**:
- Validate against all constraints
- Document constraint satisfaction
- Fail if any constraint is violated

### Validation Criteria

✅ **Correct**: All constraints measured and documented
✅ **Correct**: System operates within all constraints
❌ **Incorrect**: "It works on my machine" (constraints ignored)

---

## Principle 5: Failures are Part of the Design

### The Principle

**Error scenarios are specified for a reason. Your implementation must handle them gracefully.**

### How to Apply

**For Every Spec**:
- Identify all error scenarios
- Implement error handling for each
- Test error scenarios explicitly
- Document error behavior

**Example**:

**Specification Scenario**:
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
        parser->error_position = xml_get_error_position(root);
        return NULL;
    }
    // ... continue processing
}
```

### Validation Criteria

✅ **Correct**: All error scenarios have tests
✅ **Correct**: Error handling matches spec behavior
❌ **Incorrect**: "I handle errors" (but not the specified ones)

---

## Principle 6: Integration Before Unit Tests

### The Principle

**Integration tests validate the specification. Unit tests validate implementation details.**

### The Order of Operations

**Wrong Order**:
1. Write extensive unit tests
2. Implement all functions
3. Try to integrate at the end
4. Discover integration issues

**Right Order**:
1. Understand the spec scenarios (integration tests)
2. Write failing integration tests
3. Implement minimal code to pass
4. Add unit tests for edge cases

### Why This Works

- Integration tests are your specification scenarios
- They validate the actual requirement
- Unit tests are for implementation confidence
- Start with what matters (spec satisfaction)

### Validation Criteria

✅ **Correct**: Integration tests drive development
✅ **Correct**: Unit tests added for coverage
❌ **Incorrect**: Unit tests drive development (lose sight of spec)

---

## Principle 7: Continuous Validation

### The Principle

**Validate your implementation against the spec continuously, not just at the end.**

### How to Apply

**During Development**:
1. Implement one requirement
2. Run integration tests for that requirement
3. Fix failures
4. Move to next requirement

**After Each Commit**:
- Run relevant test suite
- Verify constraints still satisfied
- Check for regressions

**Before Marking Complete**:
- All tests pass
- All scenarios pass
- All constraints satisfied
- Code review approved

### Validation Criteria

✅ **Correct**: Continuous validation during development
✅ **Correct**: Never commit broken tests
❌ **Incorrect**: "I'll test at the end"

---

## Summary

These principles ensure your implementation:

1. ✅ Satisfies the specification (not just completes tasks)
2. ✅ Passes all specified scenarios (not just unit tests)
3. ✅ Respects all constraints (namespace, legal, build system)
4. ✅ Handles errors gracefully (as specified)
5. ✅ Maintains traceability (code → requirements)
6. ✅ Validates continuously (catch issues early)

**The goal is not to "finish the implementation" but to "satisfy the specification."**
