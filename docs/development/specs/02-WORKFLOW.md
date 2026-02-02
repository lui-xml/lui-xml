# Spec Development Workflow for Lui-XML

**Purpose**: Step-by-step workflow that ensures specification coverage and produces implementable specs.

**Status**: Follow this workflow for all spec development work.

---

## Overview

This workflow enforces the 6 core principles:
1. Specification first
2. Scenarios first
3. Spec validation
4. Follow OpenSpec format
5. Validate specification coverage
6. Continuous review

**Follow these phases in order. Do not skip phases.**

---

## Phase 1: Understanding (MUST DO FIRST)

**Time Investment**: 1-2 hours per spec
**Goal**: Understand what needs to be specified and why

### Step 1.1: Read Specification Document

**What to read**:
- docs/planning/specifications/1/README.md - The master specification
- Sections relevant to the capability
- Technical architecture descriptions
- Constraints and requirements
- Success criteria

**What to look for**:
- What problem are we solving?
- What are the technical requirements?
- What are the constraints (NO FORKING, NO SUBMODULES, namespace isolation)?
- What does "done" look like?

**Output**:
- Write down specification requirements
- Write down technical constraints
- Note dependencies on LVGL and build systems

### Step 1.2: Read Implementation Roadmap

**What to read**:
- Phase 1: Archaeology & Extraction
- Phase 2: Compatibility Engineering
- Phase 3: Build System Hardening
- Phase 4: Testing & Validation
- Phase 5: Documentation & Release

**What to look for**:
- Which phase does this capability belong to?
- What are the phase deliverables?
- What are the acceptance criteria?

### Exit Criteria

Before proceeding to Phase 2, confirm:
- [ ] I have read all relevant specification sections
- [ ] I understand the technical requirements
- [ ] I understand the constraints (namespace, legal, build system)
- [ ] I understand what "done" looks like

---

## Phase 2: Requirements Extraction (MUST DO SECOND)

**Time Investment**: 1-2 hours per spec
**Goal**: Extract requirements and map them to scenarios

### Step 2.1: Extract Requirements from Specification

**For each specification section**:
1. Identify explicit requirements ("shall", "must", "will")
2. Identify implicit requirements (implied by architecture)
3. Identify constraints (memory, LVGL version, build system)
4. Document dependencies

### Step 2.2: Map Requirements to Scenarios

**For each requirement**:
1. Identify primary success scenario
2. Identify error scenarios
3. Identify edge cases
4. Write scenarios using Given/When/Then

### Exit Criteria

Before proceeding to Phase 3, confirm:
- [ ] All specification sections extracted
- [ ] All requirements have scenarios
- [ ] Scenarios use Given/When/Then format
- [ ] Scenarios are testable

---

## Phase 3: Spec Production (MUST DO THIRD)

**Time Investment**: 1-2 hours per spec
**Goal**: Write the spec.md file

### Step 3.1: Create Spec File Structure

**Location**: `openspec/specs/<capability>/spec.md`

### Step 3.2: Write All Requirements

**For each requirement from Phase 2**:
1. Write requirement using SHALL/MUST
2. Write all scenarios using Given/When/Then
3. Include cross-references to specification sections
4. Include constraints

### Step 3.3: Create design.md (if needed)

**Create design.md if**:
- Cross-cutting concerns (multiple specs interact)
- Complex technical decisions needed
- Security or legal implications
- Multiple implementation approaches possible

### Exit Criteria

Before proceeding to Phase 4, confirm:
- [ ] Spec file created at correct location
- [ ] All requirements from Phase 2 included
- [ ] All scenarios use Given/When/Then
- [ ] Specification references documented
- [ ] Constraints documented
- [ ] Dependencies documented

---

## Phase 4: Validation (MUST DO FOURTH)

**Time Investment**: 30-60 minutes per spec
**Goal**: Verify spec is valid and implementable

### Step 4.1: OpenSpec Format Validation

**Run OpenSpec validator**:
```bash
openspec validate <spec-id> --strict
```

### Step 4.2: Specification Coverage Validation

**Create coverage matrix**:
```markdown
### Specification Coverage

| Specification Section | Requirement | Status |
|----------------------|------------|--------|
| Section 3.2 | Namespace Isolation | ✅ |
| Section 4.2 | Build System Integration | ✅ |

**Coverage**: 100% - All sections covered
```

### Step 4.3: Implementability Validation

**Check each requirement**:
- [ ] Is specific (not "system shall parse XML")
- [ ] Is testable (has scenarios)
- [ ] Has no contradictions
- [ ] Has no undefined terms
- [ ] Has clear acceptance criteria

### Exit Criteria

Before proceeding to Phase 5, confirm:
- [ ] openspec validate --strict passes
- [ ] Specification coverage 100%
- [ ] All requirements implementable
- [ ] All scenarios testable
- [ ] No contradictions

---

## Phase 5: Cross-Reference (MUST DO FIFTH)

**Time Investment**: 30-60 minutes per spec
**Goal**: Create traceability matrix

### Step 5.1: Map Requirements to Specification

**Create mapping**:
```markdown
### Specification Traceability

| Requirement | Specification Section | Coverage |
|-------------|----------------------|----------|
| Namespace Isolation | Section 3.2 | ✅ |
```

### Step 5.2: Map Requirements to Roadmap Phases

```markdown
### Roadmap Phase Traceability

| Requirement | Phase | Status |
|-------------|-------|--------|
| Code Extraction | Phase 1 | ✅ |
| Build System | Phase 3 | ✅ |
```

### Step 5.3: Create Traceability Document

**Document**: `openspec/specs/<capability>/traceability.md`

### Exit Criteria

Before proceeding to Phase 6, confirm:
- [ ] All requirements trace to specification
- [ ] All requirements trace to roadmap phases
- [ ] Traceability document created
- [ ] No orphaned requirements

---

## Phase 6: Review (MUST DO SIXTH)

**Time Investment**: 30-60 minutes per spec
**Goal**: Peer review and feedback

### Step 6.1: Self-Review

**Checklist**:
- [ ] All 6 phases complete
- [ ] All exit criteria met
- [ ] Spec validates with openspec validate --strict
- [ ] Specification coverage 100%
- [ ] All requirements implementable
- [ ] Traceability complete

### Step 6.2: Peer Review Request

**Create review request**:
```markdown
# Spec Review Request: [Capability Name]

## Summary
[1-2 paragraph summary]

## Validation Results
- OpenSpec validate: ✅ PASS
- Specification coverage: ✅ 100%
- Implementability: ✅ All requirements implementable
```

### Step 6.3: Incorporate Feedback

**Process feedback**:
1. Document all feedback
2. Categorize: must-fix, should-fix, nice-to-have
3. Implement must-fix changes
4. Validate changes
5. Re-submit for review if needed

### Exit Criteria

Before proceeding to Phase 7, confirm:
- [ ] Self-review complete
- [ ] Peer review requested
- [ ] Feedback received
- [ ] Feedback incorporated
- [ ] Re-validation passes
- [ ] Approval received

---

## Phase 7: Baseline (FINAL STEP)

**Time Investment**: 15-30 minutes per spec
**Goal**: Mark spec as ready for implementation

### Step 7.1: Final Validation

**Run final checks**:
```bash
# Final OpenSpec validation
openspec validate <spec-id> --strict

# Verify specification coverage
# (manual check of coverage matrix)

# Verify implementability
# (manual review of all requirements)
```

### Step 7.2: Create Baseline Document

**Document**: `openspec/specs/<capability>/BASELINE.md`

### Step 7.3: Mark Baseline

**Update spec header**:
```markdown
# [Capability Name]

**Status**: BASELINED - Ready for Implementation
**Baseline Date**: [Date]
**Version**: 1.0
```

### Exit Criteria

Final confirmation:
- [ ] All 7 phases complete
- [ ] All validation checks pass
- [ ] Specification coverage 100%
- [ ] Peer review approved
- [ ] Baseline document created
- [ ] Spec marked as baselined

---

## Common Workflow Violations

### ❌ Skipping Phase 1 (Understanding)

**Symptom**: Starting spec development without reading specification

**Consequence**: Missing requirements, incomplete coverage

**Fix**: Always start with Phase 1. No exceptions.

---

### ❌ Skipping Phase 2 (Requirements Extraction)

**Symptom**: Writing requirements directly from roadmap

**Consequence**: Missed specification requirements, incomplete spec

**Fix**: Always extract from specification first.

---

## Quick Reference Workflow

```
1. UNDERSTAND
   Read specification sections
   Read roadmap phases
   Document requirements

2. EXTRACT REQUIREMENTS
   Extract from specification
   Map to scenarios
   Verify scenario coverage

3. WRITE SPEC
   Create spec.md
   Write all requirements
   Write all scenarios

4. VALIDATE
   Run openspec validate --strict
   Verify specification coverage
   Verify implementability

5. CROSS-REFERENCE
   Map to specification
   Map to roadmap phases

6. REVIEW
   Self-review
   Peer review
   Incorporate feedback

7. BASELINE
   Final validation
   Create baseline document
   Mark ready for implementation
```

---

## Summary

**Follow all 7 phases in order.**
**Do not skip phases.**
**Validate continuously.**
**Focus on specification coverage.**
**Verify implementability, not format.**

**This is the path to successful spec development.**

---

**Next**: See [03-SPEC-PRODUCTION.md](./03-SPEC-PRODUCTION.md) for detailed spec production techniques.
