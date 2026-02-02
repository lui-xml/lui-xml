# Implementation Workflow

**Purpose**: The step-by-step workflow for implementing features from OpenSpec specifications.

**Workflow Type**: Specification-Driven Development (SDD)

---

## Overview

This workflow defines how to implement features from OpenSpec specifications. Unlike traditional agile where you might start coding immediately, this workflow emphasizes understanding, validation, and continuous verification against the specification.

---

## Phase 1: Understanding (Read Before You Code)

**Goal**: Thoroughly understand the specification before writing any code.

### Steps

1. **Read the Specification**
   - Open `specs/[capability]/spec.md` (or delta spec in `changes/[change-id]/specs/[capability]/spec.md`)
   - Read all requirements
   - Read all scenarios (Given/When/Then)
   - Understand the specification/roadmap references

2. **Read the Design Document**
   - Open `design.md` if it exists
   - Understand architectural decisions
   - Review constraints and trade-offs
   - Note any open questions

3. **Read Supporting Documentation**
   - Read `project.md` for conventions
   - Read related specs for dependencies
   - Review specification document sections if needed

4. **Document Your Understanding**
   - Write a brief summary of what you're implementing
   - List all requirements you need to satisfy
   - List all scenarios you need to pass
   - Identify dependencies on LVGL, CMake, ESP-IDF

### Exit Criteria

- [ ] I can explain the spec in my own words
- [ ] I understand all requirements and scenarios
- [ ] I understand all constraints (namespace, legal, build system)
- [ ] I have documented my understanding

---

## Phase 2: Planning (Design Before You Code)

**Goal**: Create a plan for satisfying the specification.

### Steps

1. **Analyze Requirements**
   - Group related requirements
   - Identify implementation order
   - Note dependencies on LVGL and build systems

2. **Design the Solution**
   - Sketch the architecture (if not already in design.md)
   - Identify modules, functions, data structures
   - Plan error handling

3. **Plan the Tests**
   - List all scenarios from the spec
   - Create a test for each scenario
   - Plan test order

4. **Estimate Constraints**
   - Verify namespace requirements (lui_/luixml_)
   - Verify LVGL version compatibility
   - Verify build system requirements

### Exit Criteria

- [ ] Implementation plan documented
- [ ] All tests identified
- [ ] Constraints verified achievable
- [ ] Dependencies identified and satisfied

---

## Phase 3: Implementation (Code to Satisfy Spec)

**Goal**: Write code that satisfies all requirements and scenarios.

### Steps

1. **Set Up Test Infrastructure**
   - Create test file for the capability
   - Set up test framework
   - Configure mocks for dependencies (LVGL, filesystem)

2. **Write Failing Tests First**
   - Write test for first scenario
   - Run test (should fail)
   - This is your starting point

3. **Implement to Pass Tests**
   - Write minimal code to pass the test
   - Run test again
   - Iterate until test passes

4. **Handle Success Scenarios**
   - Write test for success scenario
   - Implement code
   - Verify scenario passes

5. **Handle Error Scenarios**
   - Write test for error scenario
   - Implement error handling
   - Verify error handling works as specified

6. **Satisfy Constraints**
   - Verify namespace usage (grep for forbidden lv_xml_)
   - Verify build system integration
   - Verify legal constraints (provenance documentation)

7. **Add Unit Tests**
   - Add unit tests for edge cases
   - Increase coverage
   - Document implementation details

8. **Repeat for All Requirements**
   - Move to next requirement
   - Follow steps 2-7
   - Until all requirements complete

### During Implementation

**DO**:
- Read the spec again if you're unsure
- Reference requirements in code comments
- Commit frequently with spec references
- Ask questions if spec is ambiguous

**DON'T**:
- Add features not in spec (gold-plating)
- Ignore namespace constraints
- Skip error scenarios
- Assume you "know what's needed"

### Exit Criteria

- [ ] All requirements implemented
- [ ] All scenarios passing
- [ ] All constraints satisfied
- [ ] Code reviewed

---

## Phase 4: Validation (Verify Spec Satisfaction)

**Goal**: Ensure your implementation satisfies the specification.

### Steps

1. **Run All Tests**
   - Run integration tests (spec scenarios)
   - Run unit tests
   - Verify all pass

2. **Validate Constraints**
   - Verify namespace isolation (no lv_xml_ symbols)
   - Verify LVGL version compatibility
   - Verify build system integration (CMake, ESP-IDF)

3. **Validate in Production-Like Environment**
   - Test on target platform if available
   - Verify real-world behavior
   - Check for integration issues

4. **Document Validation Results**
   - Record test results
   - Document constraint satisfaction
   - Note any deviations from spec

### Exit Criteria

- [ ] All tests passing
- [ ] All constraints satisfied
- [ ] Production-like environment validated
- [ ] Validation documented

---

## Phase 5: Review (Peer Validation)

**Goal**: Get approval that your implementation satisfies the specification.

### Steps

1. **Self-Review**
   - Review all code against spec
   - Verify all requirements satisfied
   - Check all scenarios passing
   - Document any deviations

2. **Create Pull Request**
   - Reference the spec (e.g., "Refs: xml-parser/spec.md")
   - Describe what you implemented
   - Highlight any deviations

3. **Address Feedback**
   - Respond to review comments
   - Make requested changes
   - Re-validate if needed

### Exit Criteria

- [ ] Self-review complete
- [ ] Pull request created
- [ ] Reviewer approved
- [ ] All feedback addressed

---

## Phase 6: Baseline (Mark Complete)

**Goal**: Mark the implementation as complete and ready for production.

### Steps

1. **Final Verification**
   - Run full test suite
   - Verify all constraints
   - Check for regressions

2. **Update Documentation**
   - Update README if needed
   - Document any deviations from spec
   - Add usage examples

3. **Mark Complete**
   - Close tasks in tasks.md
   - Tag version if appropriate
   - Archive design notes if useful

### Exit Criteria

- [ ] Implementation verified
- [ ] Documentation updated
- [ ] Marked complete
- [ ] Ready for deployment

---

## Workflow Summary

**The Workflow in One Sentence**:

> Read spec → Plan implementation → Write tests → Implement to pass tests → Validate → Review → Complete

**The Key Insight**:

> "Tests are the specification scenarios in executable form. Implement to make tests pass, and you'll satisfy the specification."

---

## Anti-Patterns to Avoid

### Anti-Pattern 1: Implement First, Test Later

**Wrong**:
1. Write all the code
2. Try to write tests afterward
3. Realize you misunderstood the requirement

**Correct**:
1. Write tests from spec scenarios
2. Implement to make tests pass
3. Verify understanding

### Anti-Pattern 2: Ignore Constraints

**Wrong**:
- "I'll optimize namespace later"
- "Build system doesn't matter yet"
- "I'll handle errors at the end"

**Correct**:
- Design within constraints from start
- Verify namespace continuously (grep for lv_xml_)
- Handle errors from the beginning

### Anti-Pattern 3: Add Extra Features

**Wrong**:
- "This would be nice to have"
- "Users might want this"
- "I'll add this bonus feature"

**Correct**:
- Implement exactly what spec requires
- No gold-plating
- No extra features

### Anti-Pattern 4: Skip Error Scenarios

**Wrong**:
- "I'll implement error handling later"
- "Let me get the happy path working first"

**Correct**:
- Implement error scenarios alongside success scenarios
- Error handling is part of the spec
- Must be complete

---

## Quick Reference

**The 6 Phases**:
1. Understanding (Read spec)
2. Planning (Design solution)
3. Implementation (Code to pass tests)
4. Validation (Verify spec satisfaction)
5. Review (Peer approval)
6. Baseline (Mark complete)

**Golden Rule**:

> **"Test the spec, not the code."**
>
> If your tests match the spec scenarios, and your code passes the tests, your implementation satisfies the specification.

---

**Next**: Read `03-CODE-PRODUCTION.md` to learn about writing code that satisfies specifications.
