# ANTI-PATTERNS TO AVOID - CRITICAL WARNINGS

**Purpose**: Critical anti-patterns that will cause immediate rejection in code review.

**Status**: NON-NEGOTIABLE - Violating these will result in code rejection.

---

## CRITICAL: TODOs and Placeholders in Production Code

### THE ABSOLUTE RULE

**NEVER, under any circumstances, submit production code containing:**

1. **TODO comments in production code paths**
2. **Placeholder implementations**
3. **Stub functions that don't actually work**
4. **Mock implementations in production code**
5. **Hardcoded placeholder values**
6. **"For now" workarounds**
7. **"Future work" notes in critical paths**

### Why This Is Non-Negotiable

#### 1. It's Dishonest

Marking a task as [x] complete when the code contains TODOs is lying about completion.

```
❌ WRONG: [x] Implement XML parser
    Code contains: // TODO: Implement actual XML parsing

✅ CORRECT: [ ] Implement XML parser
    Leave task incomplete until actually implemented
```

#### 2. It Creates Security Vulnerabilities

```c
❌ CRITICAL VULNERABILITY:
static const char namespace_prefix[] = "lv_xml";  // TODO: Change to lui_ prefix
// Result: Symbol collision with LVGL if they reintroduce XML!
```

This is not a "TODO" - this is a **security vulnerability** that violates namespace isolation requirements.

#### 3. It Wastes Everyone's Time

- You write placeholder code
- Tests pass against placeholders (false confidence)
- Someone tries to integrate and it doesn't work
- You have to redo it anyway
- Total effort: 160% instead of 100%

#### 4. It Creates Production Deployment Risk

Someone might see "all tasks complete" and deploy to production, not realizing the code is full of TODOs.

---

## Real Examples from This Project (What NOT to Do)

### Critical: Namespace Isolation Violation

```c
// src/lui_xml_parser.c:23
/* TODO: Rename all symbols from lv_xml to lui_xml namespace */
lv_xml_parser_t *lv_xml_parser_create(void)
```

**Impact**: Symbol collision risk if LVGL reintroduces XML functionality.

**Correct Approach**:
```c
// Complete namespace migration during extraction
lui_xml_parser_t *lui_xml_create(void)
luixml_widget_register_fn_t luixml_widget_register(...)
```

### Missing Feature: Placeholder Parser

```c
// src/parser/xml_parser.c:50
/* TODO: Implement actual XML parsing
 * For now, returning mock object.
 */
lv_obj_t *lui_xml_load(const char *xml_string) {
    return NULL;  // Placeholder
}
```

**Impact**: XML parsing does NOT actually work.

**Correct Approach**:
```c
// Implement actual XML parsing
lv_obj_t *lui_xml_load(lui_xml_parser_t *parser, const char *xml_string) {
    xml_node_t *root = xml_parse_string(xml_string);
    if (!root) return NULL;
    return build_lvgl_object_tree(root);
}
```

### Build System Mock

```c
// CMakeLists.txt:42
# TODO: Implement LVGL detection
message("Assuming LVGL exists")
```

**Impact**: Build fails if LVGL is not properly detected.

**Correct Approach**:
```cmake
# Proper LVGL target detection
if(NOT TARGET lvgl)
    message(FATAL_ERROR "Lui-XML requires LVGL target. Include LVGL first.")
endif()
```

---

## The Irony: It's Actually Easier to Do It Right

| Approach | Initial Time | Total Time | Quality |
|----------|--------------|------------|---------|
| **Do it properly** | 100% | 100% | Production-ready |
| **TODO placeholders** | 60% | 160% | Must be redone |

When you use placeholders:
- You still need to understand the requirement
- You still need to design the solution
- You waste time writing placeholder code
- You waste time writing tests against stubs
- You need to redo it all later anyway

**Conclusion**: There's no time savings. Just do it right the first time.

---

## When Are Placeholders Acceptable?

### ✅ ACCEPTABLE: Test Mocks

```c
// In tests ONLY - this is appropriate
void test_xml_parsing() {
    mock_lvgl_display();
    result = lui_xml_load(test_xml);
    assert(result != NULL);
}
```

### ✅ ACCEPTABLE: Explicit Prototype Code

```c
// PROTOTYPE-ONLY - This file is exploratory and will be deleted
// prototypes/experimental_parser.c
// DO NOT DEPLOY
```

### ✅ ACCEPTABLE: Out-of-Scope Features

```c
// Phase 1: XML parser implemented
// Phase 5: JSON support (not yet implemented - tracked in tasks.md)
```

This is acceptable IF:
- The feature is explicitly documented as out-of-scope
- The current phase is complete without it
- No TODO exists in the code

### ❌ UNACCEPTABLE: Production Code Paths

```c
// NEVER THIS:
int critical_function() {
    // TODO: Implement actual logic
    return 0;  // Placeholder
}
```

---

## Code Review Checklist: TODO/Placeholder Detection

Before submitting any code for review, verify:

### Source Code Check

```bash
# Check for TODO/FIXME/HACK/XXX in source code
grep -r "TODO\|FIXME\|HACK\|XXX\|STUB\|PLACEHOLDER" src/ --include="*.c" --include="*.h"

# If any results: FAIL CODE REVIEW
```

### Namespace Isolation Check

```bash
# Check for legacy namespace symbols
grep -r "lv_xml_\|LV_XML_" src/ --include="*.c" --include="*.h"

# If any results: CRITICAL ISSUE - Must use lui_ or luixml_ prefixes
```

### Mock Check

```bash
# Check for mock implementations in production code
grep -r "mock\|Mock\|MOCK\|PLACEHOLDER\|placeholder" src/ --include="*.c"

# If results outside of tests/: FAIL CODE REVIEW
```

### Implementation Completeness

Before marking a task [x] complete:

- [ ] Function actually implements the required logic
- [ ] No TODO comments in the implementation
- [ ] No placeholder values
- [ ] No "for now" comments
- [ ] No mock implementations in production code
- [ ] Namespace constraints satisfied (lui_/luixml_ only)
- [ ] Tests pass against real implementation, not stubs

---

## What to Do Instead

### If You Can't Implement It Now

1. **Don't write the code at all**
2. **Leave the task unmarked**
3. **Document what's needed**
4. **Implement when ready**

```c
// DON'T DO THIS:
int incomplete_function() {
    // TODO: Implement later
    return 0;
}

// INSTEAD: Don't create the function yet.
// Leave the task unmarked in tasks.md
// When you're ready to implement, do it completely.
```

### If You Need a Temporary Solution

1. **Make it explicit in the task file**
2. **Use a feature flag**
3. **Document the limitation**

```c
// tasks.md
- [ ] Implement XML parser with full namespace migration (BLOCKED: waiting for Phase 1 extraction)

// In code:
#ifdef FEATURE_EXPERIMENTAL_PARSER
    parse_xml_experimental(xml_string);
#else
    LOG_ERR("XML parser not available - implement parser first");
    return LUI_XML_ERROR_NOT_IMPLEMENTED;
#endif
```

---

## Summary: The Golden Rules

1. **Never submit code with TODOs in production paths**
2. **Never use placeholder values in critical code**
3. **Never use mock implementations in production code**
4. **Never mark a task [x] if it has TODOs**
5. **Always implement complete functionality before submitting**
6. **Always maintain namespace isolation (lui_/luixml_)**
7. **If you can't implement it now, don't write the code**

---

## The Bottom Line

> **"TODOs in production code are not acceptable. They represent incomplete work that creates integration failures, technical debt, and violates namespace isolation requirements. Do it right the first time, or don't do it at all."**

**When in doubt**: Leave the task unmarked and implement it when you can do it completely.

---

**Next**: Read `01-PRINCIPLES.md` to understand the foundational principles of specification-driven implementation.
