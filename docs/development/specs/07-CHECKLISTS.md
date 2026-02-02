# Spec Development Checklists

**Purpose**: Ready-to-use checklists for ensuring spec development process compliance.

**Usage**: Print these checklists and use them for all spec development work.

---

## Pre-Spec Development Checklist

**Use this checklist BEFORE writing any spec requirements.**

### Understanding

- [ ] I have read the relevant specification sections
- [ ] I understand the technical requirements
- [ ] I understand the constraints (NO FORKING, NO SUBMODULES, namespace isolation)
- [ ] I can explain the requirements in my own words
- [ ] I understand what "done" looks like

### Roadmap Phases

- [ ] I have read the relevant roadmap phases
- [ ] I understand the phase deliverables
- [ ] I understand the success criteria

### Requirements Analysis

- [ ] I have extracted requirements from specification
- [ ] I have mapped requirements to roadmap phases
- [ ] I have identified constraints
- [ ] I have created a requirements document

### OpenSpec Format

- [ ] I have read OpenSpec AGENTS.md
- [ ] I understand SHALL vs MUST vs MAY
- [ ] I understand scenario format (Given/When/Then)
- [ ] I have read existing spec examples
- [ ] I know how to run openspec validate

**Only proceed when ALL items are checked.**

---

## Spec Development Progress Checklist

**Use this checklist DURING spec development to track progress.**

### Phase 1: Understanding ✅

- [ ] Specification sections read
- [ ] Roadmap phases read
- [ ] Requirements documented
- [ ] Constraints identified
- [ ] Dependencies identified

### Phase 2: Requirements Extraction

- [ ] Requirements extracted from specification
- [ ] Requirements mapped to roadmap phases
- [ ] Scenarios drafted for each requirement
- [ ] Error scenarios identified
- [ ] Scenario coverage verified

### Phase 3: Spec Production

- [ ] Spec file created (openspec/specs/<capability>/spec.md)
- [ ] Purpose section written
- [ ] Scope section written
- [ ] Dependencies section written
- [ ] All requirements written (with SHALL/MUST)
- [ ] All scenarios written (with Given/When/Then)
- [ ] Constraints section written
- [ ] design.md created (if needed)

### Phase 4: Validation

- [ ] openspec validate --strict passes
- [ ] Specification coverage verified (100%)
- [ ] Roadmap phase coverage verified (100%)
- [ ] All requirements implementable
- [ ] All scenarios testable
- [ ] No contradictions found

### Phase 5: Cross-Reference

- [ ] Traceability matrix created
- [ ] Specification → requirements mapped
- [ ] Roadmap → requirements mapped
- [ ] No orphaned requirements
- [ ] No orphaned artifacts

### Phase 6: Review

- [ ] Self-review complete
- [ ] Peer review requested
- [ ] Feedback received
- [ ] Feedback incorporated
- [ ] Re-validation passes

### Phase 7: Baseline

- [ ] Final validation passes
- [ ] Baseline document created
- [ ] Spec marked as baselined
- [ ] Ready for implementation

**Can mark complete when ALL phases complete.**

---

## Spec Completion Checklist

**Use this checklist BEFORE marking any spec complete.**

### Specification Coverage

- [ ] All specification sections covered
- [ ] All explicit requirements mapped
- [ ] All implicit requirements mapped
- [ ] All constraints documented
- [ ] Coverage = 100%

### Roadmap Phase Coverage

- [ ] All relevant phases covered
- [ ] All phase deliverables addressed
- [ ] All success criteria addressed
- [ ] Coverage = 100%

### Requirements Quality

- [ ] All requirements use SHALL/MUST
- [ ] All requirements specific (not vague)
- [ ] All requirements implementable
- [ ] All requirements have source references
- [ ] No implementation details in requirements

### Scenarios Quality

- [ ] Every requirement has ≥1 scenario
- [ ] All scenarios use Given/When/Then
- [ ] All scenarios testable
- [ ] Success scenarios present
- [ ] Error scenarios present (where applicable)
- [ ] No subjective language

### Validation

- [ ] openspec validate --strict passes
- [ ] No format errors
- [ ] No missing scenarios
- [ ] No missing sections

### Traceability

- [ ] Specification → requirements mapping complete
- [ ] Roadmap → requirements mapping complete
- [ ] Traceability document created
- [ ] No orphaned requirements

### Technical Accuracy

- [ ] Constraints realistic (LVGL version, memory, legal)
- [ ] Dependencies correct (LVGL, CMake, ESP-IDF)
- [ ] Resource requirements specified
- [ ] Performance criteria specified
- [ ] Legal constraints documented (MIT, provenance)

### Documentation

- [ ] spec.md complete
- [ ] design.md complete (if needed)
- [ ] traceability.md complete
- [ ] BASELINE.md complete

**If ANY item unchecked, spec is NOT complete.**

---

## Spec Review Checklist

**Use this checklist when reviewing someone else's spec.**

### Understanding

- [ ] Specification sections identified
- [ ] Roadmap phases identified
- [ ] Requirements clearly sourced
- [ ] Success criteria clear
- [ ] Acceptance criteria clear

### Coverage

- [ ] Specification coverage 100%
- [ ] Roadmap coverage 100%
- [ ] No missing requirements
- [ ] No orphaned artifacts

### Requirements Quality

- [ ] All requirements use SHALL/MUST
- [ ] All requirements specific
- [ ] All requirements implementable
- [ ] No implementation details
- [ ] No contradictions

### Scenarios Quality

- [ ] All requirements have scenarios
- [ ] All scenarios use Given/When/Then
- [ ] All scenarios testable
- [ ] Success scenarios present
- [ ] Error scenarios present

### Validation

- [ ] openspec validate --strict passes
- [ ] Specification coverage verified
- [ ] Implementability verified
- [ ] Traceability complete

### Traceability

- [ ] All requirements trace to specification
- [ ] All requirements trace to roadmap
- [ ] Traceability document exists

**Request changes if ANY item unchecked.**

---

## Continuous Spec Review Checklist

**Use this checklist AFTER EVERY spec change.**

### Quick Checks (2 minutes)

- [ ] openspec validate --strict still passes
- [ ] No obvious format errors
- [ ] No missing scenarios

### Coverage Checks (5 minutes)

- [ ] New requirement has specification reference
- [ ] New requirement has roadmap phase reference
- [ ] New requirement has scenarios

### Quality Checks (5 minutes)

- [ ] New requirements specific (not vague)
- [ ] New scenarios testable
- [ ] No contradictions introduced
- [ ] Traceability updated

### Documentation Checks (5 minutes)

- [ ] Traceability document updated
- [ ] Coverage matrix updated
- [ ] Constraints documented

**If ANY check fails, fix immediately before continuing.**

---

## Self-Correction Checklist

**Use this checklist when you feel stuck or unsure.**

### Understanding

- [ ] Can I explain the requirements in my own words?
- [ ] Do I understand the specification sections?
- [ ] Do I understand the roadmap phases?
- [ ] Do I know what "done" looks like?

### Approach

- [ ] Am I reading specification first?
- [ ] Am I extracting requirements (not inventing)?
- [ ] Am I writing specific requirements?
- [ ] Am I focusing on coverage, not word count?

### Scenarios

- [ ] Do all requirements have scenarios?
- [ ] Do scenarios use Given/When/Then?
- [ ] Are scenarios testable?
- [ ] Are error scenarios included?

### Validation

- [ ] Have I run openspec validate --strict?
- [ ] Is specification coverage 100%?
- [ ] Are all requirements implementable?
- [ ] Is traceability complete?

### Red Flags

- [ ] Am I writing vague requirements?
- [ ] Am I writing untestable scenarios?
- [ ] Am I including implementation details?
- [ ] Am I skipping error scenarios?
- [ ] Am I missing specification coverage?
- [ ] Am I missing traceability?

**If ANY red flag: Stop and reassess approach.**

---

## Pre-Implementation Spec Review Checklist

**Use this checklist BEFORE implementation begins.**

### Spec Completeness

- [ ] Spec is baselined
- [ ] All 7 development phases complete
- [ ] All validation checks pass
- [ ] Peer review approved
- [ ] No open questions

### Coverage Verified

- [ ] Specification coverage 100%
- [ ] Roadmap coverage 100%
- [ ] Traceability complete

### Implementability Verified

- [ ] All requirements specific
- [ ] All scenarios testable
- [ ] No contradictions
- [ ] Constraints documented
- [ ] Dependencies clear

### Documentation Complete

- [ ] spec.md complete
- [ ] design.md complete (if needed)
- [ ] traceability.md complete
- [ ] BASELINE.md complete

### Approval Granted

- [ ] Self-review complete
- [ ] Peer review complete
- [ ] Feedback incorporated
- [ ] Final validation passes
- [ ] Approved for implementation

**If ANY unchecked, implementation CANNOT begin.**

---

## Capability-Specific Checklist Template

**Customize this for each capability you develop.**

### Pre-Development

- [ ] Read [capability] specification sections
- [ ] Read [capability] roadmap phases
- [ ] Document [capability] requirements
- [ ] Create [capability] coverage matrix

### During Development

- [ ] Extract [capability] requirements from specification
- [ ] Map [capability] requirements to roadmap phases
- [ ] Write [capability] scenarios
- [ ] Validate [capability] implementability
- [ ] Create [capability] traceability

### Completion

- [ ] Specification coverage 100% for [capability]
- [ ] All [capability] phases addressed
- [ ] [capability] spec validated
- [ ] [capability] spec baselined

---

## Quick Reference Checklist

**The "at a glance" version.**

### Before Starting
- [ ] Specification sections read
- [ ] Roadmap phases read
- [ ] Requirements documented

### During Work
- [ ] Requirements specific (not vague)
- [ ] Scenarios testable (not subjective)
- [ ] Coverage tracked (specification/phases)
- [ ] Traceability maintained

### Before Complete
- [ ] Specification coverage 100%
- [ ] All requirements implementable
- [ ] All scenarios testable
- [ ] Traceability complete
- [ ] Validation passes
- [ ] Review approved

### Continuous
- [ ] openspec validate --strict passes
- [ ] No regressions
- [ ] Coverage maintained
- [ ] Traceability updated

**This is your safety net. Use it.**

---

## How to Use These Checklists

### For New Spec Developers

1. **Read all checklists** before starting work
2. **Print them** or keep them open
3. **Use pre-development checklist** every time
4. **Check items as you go**
5. **Don't skip items**

### For Experienced Spec Developers

1. **Review checklists periodically**
2. **Use completion checklist** before marking done
3. **Use continuous validation** after changes
4. **Use self-correction** when stuck

### For Spec Reviewers

1. **Use spec review checklist**
2. **Verify specification coverage**
3. **Verify implementability**
4. **Verify traceability**
5. **Don't approve if items unchecked**

---

## Summary

**Checklists are your safety net.**

**They prevent**:
- Forgetting critical steps
- Skipping validation
- Missing specification coverage
- Writing unimplementable requirements
- Claiming completion too early

**Use them consistently.**

**They will save you from failed specs.**

---

**End of Spec Development Guide**

**Next steps**:
1. Read all documents in this guide
2. Internalize the principles
3. Use the checklists
4. Share with your team
5. Update based on lessons learned

**These ways of working will prevent spec development failures.**

**Follow them consistently.**
