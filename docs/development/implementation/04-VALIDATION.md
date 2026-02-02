# Implementation Validation

**Purpose**: How to validate that your implementation satisfies the OpenSpec specification.

---

## Overview

Validation ensures your implementation **actually satisfies the specification**, not just that it "compiles and runs."

---

## Validation Layers

### Layer 1: Test Validation

**Goal**: Verify all tests pass and match spec scenarios.

#### What to Validate

**Test Coverage**:
- [ ] Every requirement has at least one test
- [ ] Every scenario has a corresponding test
- [ ] Both success and error scenarios tested

**Test Correctness**:
- [ ] Tests use Given/When/Then format
- [ ] Tests match spec scenarios exactly
- [ ] Tests verify spec behavior (not implementation)

#### Validation Command

```bash
# Run integration tests (spec scenarios)
./build/tests/test_xml_parser

# All tests should pass
ctest --output-on-failure
```

---

### Layer 2: Constraint Validation

**Goal**: Verify all constraints in the specification are satisfied.

#### Namespace Constraints

**Spec Constraint**: "MUST use lui_ prefix for public APIs"

**Validation**:
```bash
# Check for correct namespace
grep -r "^lui_" src/ include/ | grep -E "(lui_xml|lui_obj)" | wc -l
# Should be > 0

# Check for forbidden namespace
grep -r "lv_xml_" src/ include/
# Should return no results
```

#### Build System Constraints

**Spec Constraint**: "MUST detect LVGL target"

**Validation**:
```cmake
# Test CMake configuration
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Debug
# Should pass if LVGL target exists
# Should fail if LVGL target missing
```

#### Legal Constraints

**Spec Constraint**: "MUST preserve git authorship"

**Validation**:
```bash
# Verify authorship preserved
git log --format="%an <%ae>" src/lui_xml_parser.c | head -10
# Should show original LVGL authors, NOT committer's name
```

---

### Layer 3: Integration Validation

**Goal**: Verify the implementation works in a production-like environment.

#### What to Validate

**Dependency Integration**:
- [ ] LVGL integration works
- [ ] CMake build system integration works
- [ ] ESP-IDF component integration works

**Environment Validation**:
- [ ] Works on target platforms (not just x86)
- [ ] Works with real LVGL (not mocks)

---

### Layer 4: Spec Compliance Validation

**Goal**: Verify the implementation matches the spec exactly.

#### Compliance Checklist

For each requirement:
- [ ] **Behavior**: Does it do what the spec says?
- [ ] **Namespace**: Are lui_/luixml_ prefixes used correctly?
- [ ] **Constraints**: Are all constraints satisfied?
- [ ] **Scenarios**: Do all scenarios pass?
- [ ] **Errors**: Do error cases match spec?
- [ ] **Traceability**: Can trace code to requirement?

---

## Validation Tools

### Static Analysis

**Tools**: cppcheck, clang-tidy

**What to Check**:
- Memory leaks
- Buffer overflows
- Uninitialized variables
- Unused code

**Command**:
```bash
# Run static analysis
cppcheck src/
clang-tidy src/

# Check for namespace violations
grep -rn "lv_xml_" src/ && echo "NAMESPACE VIOLATION FOUND"
```

### Dynamic Analysis

**Tools**: Valgrind, AddressSanitizer

**What to Check**:
- Memory leaks
- Invalid memory access
- Use-after-free

**Command**:
```bash
# Run with Valgrind
valgrind --leak-check=full ./build/tests/test_xml_parser
```

---

## Validation Checklist

### Before Submitting for Review

**Test Validation**:
- [ ] All integration tests pass
- [ ] All unit tests pass
- [ ] Test coverage ≥ 80%

**Namespace Validation**:
- [ ] All public APIs use lui_ prefix
- [ ] All internal widgets use luixml_ prefix
- [ ] No lv_xml_ symbols found

**Spec Compliance**:
- [ ] All requirements implemented
- [ ] All scenarios passing
- [ ] Error cases handled as specified
- [ ] Code traces to requirements

**Code Quality**:
- [ ] No compiler warnings
- [ ] Static analysis clean
- [ ] No debug/TODO comments
- [ ] Code review approved

---

## Continuous Validation

### During Development

**Every Commit**:
- [ ] Tests pass locally
- [ ] Namespace verified (grep for lv_xml_)
- [ ] No regressions introduced

**Before Pushing**:
- [ ] Full test suite passes
- [ ] Static analysis clean
- [ ] Coverage not decreased

---

## Quick Reference

**The 4 Validation Layers**:
1. **Tests** - Scenarios pass
2. **Constraints** - Namespace, build system, legal
3. **Integration** - Works with LVGL and build systems
4. **Compliance** - Matches spec exactly

**The Golden Rule**:

> **"An implementation is valid when it satisfies all requirements, passes all scenarios, and respects all constraints (especially namespace isolation)."**

---

**Next**: Read `05-REQUIREMENTS-ANALYSIS.md` to learn how to analyze requirements for implementation.
