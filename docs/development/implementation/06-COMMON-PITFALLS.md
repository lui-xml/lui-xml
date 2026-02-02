# Common Implementation Pitfalls

**Purpose**: Catalog of common mistakes in implementation and how to avoid them.

**Key Benefit**: Learn from others' mistakes so you don't repeat them.

---

## Pitfall 1: The Document Completion Delusion

### What It Is

Focusing on completing implementation tasks rather than ensuring specification satisfaction.

### Symptoms

- Marking task complete when code "compiles"
- Claiming success when tests pass
- Measuring progress by task count
- Ignoring whether spec is satisfied

### How to Avoid

**Focus on specification satisfaction**:
```markdown
## Wrong Approach
Task: XML Parser
- [x] Parser code written
- [x] Tests pass
Status: COMPLETE ✅

## Correct Approach
Task: XML Parser

Specification satisfaction:
- [ ] Namespace Isolation requirement → lui_/luixml_ prefixes used
- [ ] Parser Initialization scenario → passes
- [ ] Invalid XML scenario → error handling works

Validation:
- [x] Tests pass
- [x] Namespace verified (grep: no lv_xml_)
- [x] Spec scenarios all pass

Status: COMPLETE ✅
```

**Rule**: Implementation complete only when specification satisfied.

---

## Pitfall 2: TODOs in Production Code

### What It Is

Leaving TODO comments in production code instead of implementing complete functionality.

### Symptoms

- Functions with // TODO: Implement this
- Placeholder values with // TODO: Use real value
- Mock implementations in production code

### Why It's Dangerous

**Security Risk**:
```c
// TODO: Change to lui_xml prefix
lv_xml_parser_t *parser = lv_xml_create();  // Collision risk!
```

**Integration Risk**:
```c
// TODO: Implement XML parsing
return NULL;  // Returns NULL - breaks everything!
```

### How to Avoid

**Implement completely or not at all**:
```markdown
❌ WRONG:
int parse_xml() {
    // TODO: Implement parsing
    return 0;  // Placeholder
}

✅ CORRECT:
// Don't write the function until ready
// Leave task unmarked in tasks.md
// When ready, implement completely
int parse_xml() {
    xml_node_t *root = xml_parse_string(xml_string);
    if (!root) return PARSE_ERROR;
    return process_xml(root);
}
```

**Rule**: Never submit code with TODOs in production paths.

---

## Pitfall 3: Namespace Violations

### What It Is

Using forbidden prefixes (lv_xml_) instead of required prefixes (lui_/luixml_).

### Symptoms

- Code uses lv_xml_parser, lv_xml_load, etc.
- Internal widget files use lv_xml_button instead of luixml_button
- Symbol collision risk with LVGL

### Why It's Dangerous

- **Collision Risk**: If LVGL reintroduces XML, symbols will collide
- **Legal Risk**: Namespace not distinct from LVGL
- **Maintainability**: Can't distinguish Lui-XML code from LVGL code

### How to Avoid

**Enforce namespace rules**:
```bash
# Check for forbidden symbols
grep -r "lv_xml_" src/ include/

# If found: MUST FIX
# Rename to lui_xml_ or luixml_ as appropriate
```

**Correct Examples**:
```c
// Public API - lui_ prefix
lui_xml_parser_t *lui_xml_create(void);
lv_obj_t *lui_xml_load(lui_xml_parser_t *, const char *);

// Internal widgets - luixml_ prefix
int luixml_register_button(lui_xml_parser_t *);
int luixml_register_label(lui_xml_parser_t *);

// FORBIDDEN - lv_xml_ prefix
lv_xml_parser_t *lv_xml_create(void);  // DON'T DO THIS
```

**Rule**: Namespace isolation is non-negotiable. lui_/luixml_ ONLY.

---

## Pitfall 4: Missing Error Scenarios

### What It Is

Only implementing success scenarios, ignoring error conditions.

### Symptoms

- Functions assume success
- No error handling
- No tests for error cases

### Why It's Dangerous

- **Crashes**: Unhandled errors cause crashes
- **Undefined Behavior**: Invalid input produces invalid output
- **Poor UX**: Users get cryptic error messages

### How to Avoid

**Implement all specified error scenarios**:
```c
❌ WRONG: No error handling
lv_obj_t *lui_xml_load(lui_xml_parser_t *parser, const char *xml) {
    xml_node_t *root = xml_parse(xml);
    return build_object(root);  // Crashes if xml is NULL!
}

✅ CORRECT: With error handling
lv_obj_t *lui_xml_load(lui_xml_parser_t *parser, const char *xml) {
    if (!parser) {
        parser->last_error = LUI_XML_ERROR_INVALID_PARSER;
        return NULL;
    }
    
    xml_node_t *root = xml_parse(xml);
    if (xml_has_error(root)) {
        parser->last_error = LUI_XML_ERROR_SYNTAX;
        parser->error_line = xml_get_error_line(root);
        return NULL;
    }
    
    return build_object(root);
}
```

**Rule**: Every error scenario in spec must be implemented and tested.

---

## Pitfall 5: Ignoring Build System Constraints

### What It Is

Not implementing proper CMake or ESP-IDF integration.

### Symptoms

- No LVGL target detection
- Build fails when LVGL is missing
- No ESP-IDF component.yml

### Why It's Dangerous

- **Integration Failures**: Users can't build the library
- **Cryptic Errors**: Build fails with unclear messages
- **Poor UX**: Hard to integrate into projects

### How to Avoid

**Implement proper build system integration**:
```cmake
# CMakeLists.txt - Check for LVGL target
if(TARGET lvgl)
    message(STATUS "Lui-XML: Integrating with existing LVGL target")
else()
    message(FATAL_ERROR "Lui-XML requires LVGL target. Include LVGL first.")
endif()

add_library(lui_xml INTERFACE)
target_link_libraries(lui_xml INTERFACE lvgl)
```

**Test both scenarios**:
```bash
# Test 1: LVGL present - should succeed
cmake -D LVGL_DIR=../lvgl ..

# Test 2: LVGL missing - should fail with clear error
cmake ..
# Should see: FATAL_ERROR - Lui-XML requires LVGL target
```

**Rule**: Build system integration is critical for usability.

---

## Pitfall 6: Violating Legal Constraints

### What It Is

Not preserving git authorship or license information.

### Symptoms

- Git log shows committer's name instead of original authors
- No PROVENANCE.md file
- No LICENSE file
- No attribution to LVGL project

### Why It's Dangerous

- **Legal Risk**: IP ownership unclear
- **License Violation**: MIT license requires attribution
- **Trust Issues**: Can't verify code provenance

### How to Avoid

**Preserve authorship during extraction**:
```bash
# During Phase 1 extraction, use:
git filter-repo ... --preserve-commit-committer --preserve-commit-author

# Verify authorship preserved
git log --format="%an <%ae>" src/lui_xml_parser.c | head -10
# Should show original LVGL authors, NOT your name
```

**Create PROVENANCE.md**:
```markdown
# Provenance

This code originally developed as part of the LVGL project (https://github.com/lvgl/lvgl)
under MIT license. Extracted and renamed with author attribution preserved.

## Original Authors
[Git log output showing original authors]

## Extraction Method
git-filter-repo with --preserve-commit-author
...
```

**Rule**: Legal constraints are non-negotiable.

---

## Pitfall 7: Adding Extra Features

### What It Is

Implementing features not specified in the specification.

### Symptoms

- "This would be nice to have"
- "Users might want this"
- Adding JSON/YAML support when spec only requires XML

### Why It's Dangerous

- **Scope Creep**: Implementation never completes
- **Maintenance Burden**: Extra code must be maintained
- **Spec Violation**: Not what was agreed upon

### How to Avoid

**Implement ONLY what spec requires**:
```c
❌ WRONG: Extra feature not in spec
lv_obj_t *lui_xml_load_json(lui_xml_parser_t *, const char *json);
lv_obj_t *lui_xml_load_yaml(lui_xml_parser_t *, const char *yaml);

✅ CORRECT: Only what spec requires
lv_obj_t *lui_xml_load(lui_xml_parser_t *, const char *xml);
```

**Rule**: Gold-plating violates specification-driven development.

---

## Pitfall 8: Mocking Away Constraints

### What It Is

Using mocks or stubs that bypass constraints.

### Symptoms

- Tests mock namespace checks
- Tests mock LVGL integration
- Tests mock build system

### Why It's Dangerous

- **False Confidence**: Tests pass but real code fails
- **Integration Failures**: Real environment doesn't match mocks
- **Constraint Violations**: Namespace violations not caught

### How to Avoid

**Test against real constraints**:
```c
❌ WRONG: Mock namespace check
void test_namespace() {
    mock_namespace_check(true);  // Bypasses real check
    load_xml();
}

✅ CORRECT: Test real namespace
void test_namespace() {
    lui_xml_create();
    assert(symbol_count("lv_xml_") == 0);  // Real check
}
```

**Rule**: Tests must verify real constraints, not mock them.

---

## Pitfall 9: Skipping Traceability

### What It Is

Not documenting the connection between code and requirements.

### Symptoms

- Code comments don't reference spec
- Git commits don't reference requirements
- Can't explain why code exists

### Why It's Dangerous

- **Maintainability**: Future developers don't know why code exists
- **Spec Divergence**: Code drifts from spec over time
- **Review Difficulty**: Can't verify code satisfies spec

### How to Avoid

**Add traceability everywhere**:
```c
/**
 * XML Parser Creation
 *
 * Spec: xml-parser/spec.md
 * Requirement: Namespace Isolation
 * Scenario: Parser Initialization
 *
 * Creates XML parser with lui_xml namespace.
 */
lui_xml_parser_t *lui_xml_create(void);
```

```bash
git commit -m "feat(xml-parser): implement parser initialization

Implements Namespace Isolation requirement from xml-parser/spec.md

- Creates parser with lui_xml namespace
- Registers default widgets with luixml_ prefix
- Verifies no lv_xml_ symbols

Refs: xml-parser/spec.md#requirement-1"
```

**Rule**: Every line of code should trace to a requirement.

---

## Pitfall 10: Implementing Without Understanding

### What It Is

Writing code without fully understanding the specification.

### Symptoms

- "I think this is what the spec wants"
- "I'll figure it out as I go"
- Frequent rewrites due to misunderstanding

### Why It's Dangerous

- **Wasted Effort**: Implementing wrong things
- **Rewrites**: Misunderstanding requires reimplementation
- **Frustration**: Constant backtracking

### How to Avoid

**Understand before implementing**:
1. Read spec completely
2. Take notes on requirements
3. Ask questions if unclear
4. Plan implementation
5. THEN write code

```markdown
Before implementation:
- [ ] Read spec 3 times
- [ ] Can explain requirements in own words
- [ ] Created implementation plan
- [ ] All questions answered

Only then: Start coding
```

**Rule**: Understand completely, then implement.

---

## Warning Signs

### You Might Be Falling Into a Pitfall If:

- Code has TODOs
- Namespace violations (lv_xml_ symbols found)
- Error scenarios not implemented
- Extra features added
- No traceability to requirements
- Can't explain why code exists
- Mocks bypass constraints

**If any of these apply**: Stop and reassess approach.

---

## Prevention Checklist

**Before starting implementation**:
- [ ] Read all spec sections
- [ ] Understand all requirements
- [ ] Understand all constraints
- [ ] Create implementation plan

**During implementation**:
- [ ] Namespace verified (no lv_xml_)
- [ ] Error scenarios implemented
- [ ] Traceability maintained
- [ ] No TODOs added

**Before marking complete**:
- [ ] Specification satisfied
- [ ] All scenarios pass
- [ ] All constraints verified
- [ ] Traceability complete

**If ANY unchecked**: Implementation is not complete.

---

## Summary

**These pitfalls are common, avoidable, and dangerous.**

**Key prevention strategies**:
1. Focus on specification satisfaction, not task completion
2. Never use TODOs in production code
3. Enforce namespace isolation (lui_/luixml_ only)
4. Implement all error scenarios
5. Respect legal constraints (provenance, license)
6. Add extra features (not in spec)
7. Verify real constraints (don't mock them)
8. Always include traceability
9. Understand completely before coding

**Be vigilant. Check yourself against this list regularly.**

---

**Next**: See `07-CHECKLISTS.md` for ready-to-use checklists.
