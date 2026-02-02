# Implementation Checklists

**Purpose**: Ready-to-use checklists for ensuring implementation process compliance.

**Usage**: Print these checklists and use them for all implementation work.

---

## Pre-Implementation Checklist

**Use this checklist BEFORE writing any implementation code.**

### Understanding

- [ ] I have read the specification for this capability
- [ ] I understand all requirements
- [ ] I understand all scenarios (success and error)
- [ ] I understand the constraints (namespace, legal, build system)
- [ ] I can explain the requirements in my own words

### Requirements Analysis

- [ ] I have extracted functional requirements
- [ ] I have extracted constraints
- [ ] I have mapped scenarios to tests
- [ ] I have created an implementation plan

### Namespace Planning

- [ ] I know which symbols use lui_ prefix (public APIs)
- [ ] I know which symbols use luixml_ prefix (internal)
- [ ] I know to avoid lv_xml_ prefix (forbidden)
- [ ] I have grep strategy to verify namespace

### Legal Planning

- [ ] I understand provenance requirements
- [ ] I understand license requirements (MIT)
- [ ] I know how to preserve git authorship

**Only proceed when ALL items are checked.**

---

## Implementation Progress Checklist

**Use this checklist DURING implementation to track progress.**

### Phase 1: Understanding ✅

- [ ] Specification sections read
- [ ] Requirements documented
- [ ] Constraints identified
- [ ] Dependencies identified

### Phase 2: Planning

- [ ] Implementation plan documented
- [ ] All tests identified
- [ ] Constraints verified achievable
- [ ] Dependencies addressed

### Phase 3: Implementation

- [ ] Test infrastructure set up
- [ ] Failing tests written first
- [ ] Implementation passes tests
- [ ] Success scenarios implemented
- [ ] Error scenarios implemented
- [ ] Constraints satisfied
- [ ] Unit tests added

### Phase 4: Validation

- [ ] All tests passing
- [ ] Namespace verified (grep for lv_xml_)
- [ ] Build system integration tested
- [ ] Legal constraints satisfied
- [ ] Production-like environment tested

### Phase 5: Review

- [ ] Self-review complete
- [ ] Pull request created
- [ ] Feedback received
- [ ] Feedback incorporated
- [ ] Re-validation passes

### Phase 6: Baseline

- [ ] Final verification passes
- [ ] Documentation updated
- [ ] Tasks marked complete
- [ ] Ready for deployment

**Can mark complete when ALL phases complete.**

---

## Implementation Completion Checklist

**Use this checklist BEFORE marking any implementation complete.**

### Specification Satisfaction

- [ ] All requirements implemented
- [ ] All success scenarios passing
- [ ] All error scenarios passing
- [ ] Specification = 100% satisfied

### Namespace Compliance

- [ ] All public APIs use lui_ prefix
- [ ] All internal widgets use luixml_ prefix
- [ ] No lv_xml_ symbols found (verified with grep)
- [ ] Namespace tests pass

### Code Quality

- [ ] All requirements implementable
- [ ] All scenarios testable
- [ ] No contradictions
- [ ] No implementation details missing

### Testing

- [ ] Integration tests pass (spec scenarios)
- [ ] Unit tests pass
- [ ] Test coverage ≥ 80%
- [ ] Error scenarios tested

### Validation

- [ ] openspec validate passes (if applicable)
- [ ] Namespace validation passes
- [ ] Build system integration passes
- [ ] Legal constraints satisfied

### Documentation

- [ ] Code comments reference spec requirements
- [ ] Git commits reference spec requirements
- [ ] README updated (if needed)
- [ ] PROVENANCE.md exists (if applicable)

### Code Quality

- [ ] No compiler warnings
- [ ] Static analysis clean
- [ ] No TODOs in production code
- [ ] No placeholder implementations

**If ANY item unchecked, implementation is NOT complete.**

---

## Code Review Checklist

**Use this checklist when reviewing someone else's implementation.**

### Understanding

- [ ] Specification requirements identified
- [ ] Scenarios clearly understood
- [ ] Success criteria clear
- [ ] Error criteria clear

### Specification Compliance

- [ ] All requirements implemented
- [ ] All scenarios passing
- [ ] No extra features added
- [ ] No missing functionality

### Namespace Compliance

- [ ] All symbols use correct prefix (lui_/luixml_)
- [ ] No lv_xml_ symbols found
- [ ] Namespace tests pass

### Code Quality

- [ ] No TODOs in production code
- [ ] No placeholders
- [ ] No mocks in production
- [ ] Error handling complete

### Testing

- [ ] All tests passing
- [ ] Test coverage adequate
- [ ] Error scenarios tested

**Request changes if ANY item unchecked.**

---

## Continuous Implementation Review Checklist

**Use this checklist AFTER EVERY implementation change.**

### Quick Checks (2 minutes)

- [ ] Code compiles without warnings
- [ ] Tests still pass
- [ ] No obvious format errors

### Namespace Checks (5 minutes)

- [ ] No lv_xml_ symbols introduced
- [ ] New code uses lui_/luixml_ prefixes
- [ ] Namespace tests still pass

### Quality Checks (5 minutes)

- [ ] No TODOs added
- [ ] No placeholders added
- [ ] Error handling included
- [ ] Traceability updated

**If ANY check fails, fix immediately before continuing.**

---

## Self-Correction Checklist

**Use this checklist when you feel stuck or unsure.**

### Understanding

- [ ] Can I explain the requirements?
- [ ] Do I understand the scenarios?
- [ ] Do I understand the constraints?
- [ ] Do I know what "done" looks like?

### Approach

- [ ] Am I reading specification first?
- [ ] Am I implementing only what's required?
- [ ] Am I verifying namespace continuously?
- [ ] Am I focusing on spec satisfaction?

### Code Quality

- [ ] Do all functions have error handling?
- [ ] Are namespace constraints satisfied?
- [ ] Are error scenarios implemented?
- [ ] Is traceability maintained?

### Red Flags

- [ ] Am I writing TODOs?
- [ ] Am I using lv_xml_ prefix?
- [ ] Am I adding extra features?
- [ ] Am I mocking constraints?
- [ ] Am I skipping error scenarios?

**If ANY red flag: Stop and reassess approach.**

---

## Pre-Deployment Checklist

**Use this checklist BEFORE deploying to production.**

### Implementation Completeness

- [ ] All phases complete
- [ ] All validation checks pass
- [ ] Code review approved
- [ ] No open blockers

### Specification Compliance

- [ ] Specification satisfaction 100%
- [ ] All scenarios passing
- [ ] All constraints satisfied
- [ ] Traceability complete

### Namespace Verification

- [ ] grep -r "lv_xml_" src/ returns nothing
- [ ] grep -r "^lui_" src/ finds all public APIs
- [ ] grep -r "luixml_" src/ finds all widgets

### Build System Verification

- [ ] CMake integration works
- [ ] ESP-IDF component works (if applicable)
- [ ] LVGL detection works

### Legal Verification

- [ ] PROVENANCE.md exists
- [ ] LICENSE file exists (MIT)
- [ ] Git authorship preserved
- [ ] Attribution to LVGL included

### Testing

- [ ] All tests pass
- [ ] Integration tests pass
- [ ] Unit tests pass
- [ ] Coverage ≥ 80%

**If ANY unchecked, deployment CANNOT proceed.**

---

## Namespace-Specific Checklist

**Lui-XML Critical: Namespace Isolation**

### Before Writing Code

- [ ] I know lui_ is for public APIs (lui_xml_create, lui_xml_load)
- [ ] I know luixml_ is for internal widgets (luixml_button, luixml_label)
- [ ] I know lv_xml_ is FORBIDDEN

### During Implementation

- [ ] Function names use lui_ prefix (public)
- [ ] Internal widget files use luixml_ prefix
- [ ] grep -r "lv_xml_" src/ returns nothing

### Before Submitting

- [ ] Reviewed all function names for correct prefix
- [ ] Ran final namespace grep check
- [ ] No lv_xml_ symbols in code
- [ ] All namespace tests pass

**CRITICAL**: Namespace violations will cause immediate rejection.

---

## Quick Reference Checklist

**The "at a glance" version.**

### Before Starting
- [ ] Spec sections read
- [ ] Requirements documented
- [ ] Constraints understood

### During Work
- [ ] Namespace verified (lui_/luixml_ only)
- [ ] No TODOs added
- [ ] Error handling included
- [ ] Traceability maintained

### Before Complete
- [ ] Spec satisfaction 100%
- [ ] All scenarios passing
- [ ] Namespace verified (no lv_xml_)
- [ ] Legal constraints satisfied
- [ ] Tests passing
- [ ] Review approved

### Continuous
- [ ] Code compiles
- [ ] Tests pass
- [ ] No regressions
- [ ] Namespace maintained

**This is your safety net. Use it.**

---

## How to Use These Checklists

### For New Implementers

1. **Read all checklists** before starting work
2. **Print them** or keep them open
3. **Use pre-implementation checklist** every time
4. **Check items as you go**
5. **Don't skip items**

### For Experienced Implementers

1. **Review checklists periodically**
2. **Use completion checklist** before marking done
3. **Use continuous validation** after changes
4. **Use self-correction** when stuck

### For Code Reviewers

1. **Use code review checklist**
2. **Verify namespace compliance**
3. **Verify specification satisfaction**
4. **Verify traceability**
5. **Don't approve if items unchecked**

---

## Summary

**Checklists are your safety net.**

**They prevent**:
- Forgetting critical steps
- Skipping validation
- Missing specification coverage
- Writing code with TODOs
- Violating namespace constraints
- Claiming completion too early

**Use them consistently.**

**They will save you from failed implementations.**

---

**End of Implementation Guide**

**Next steps**:
1. Read all documents in this guide
2. Internalize the principles
3. Use the checklists
4. Share with your team
5. Update based on lessons learned

**These ways of working will prevent implementation failures.**

**Follow them consistently.**
