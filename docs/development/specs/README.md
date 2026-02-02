# Spec Development Guide for Lui-XML

**Purpose**: Complete guide for developing OpenSpec specifications for the Lui-XML project.

**Status**: NON-NEGOTIABLE - Follow this guide for all spec development work.

---

## Overview

This guide provides principles and workflow for **spec development**.

**Key characteristics**:
- **Input**: Specification document, implementation roadmap
- **Output**: OpenSpec specs (requirements + scenarios)
- **Validation**: Spec is implementable, complete, accurate
- **Success Metric**: Specification coverage, implementable specs

---

## Guide Structure

This guide contains 7 documents that must be followed in order:

### 1. [01-PRINCIPLES.md](./01-PRINCIPLES.md)
**Core principles** that guide all spec development work.

**Key principles**:
1. **Specification First** - Read specification before writing specs
2. **Scenarios First** - Every requirement needs testable scenarios
3. **Spec Validation** - Implementable specs, not word count
4. **Follow OpenSpec Format** - Don't invent without checking
5. **Spec Completeness ≠ Coverage** - Validate specification coverage
6. **Continuous Review** - Review against specification continuously

**Read this first** to understand the philosophy.

---

### 2. [02-WORKFLOW.md](./02-WORKFLOW.md)
**Step-by-step workflow** ensuring specification coverage and implementable specs.

**7-Phase Workflow**:
1. **Understanding** - Read specification and roadmap
2. **Requirements Extraction** - Extract requirements and map to scenarios
3. **Spec Production** - Write spec.md with all requirements and scenarios
4. **Validation** - Run openspec validate, verify coverage
5. **Cross-Reference** - Create traceability matrix
6. **Review** - Peer review and feedback
7. **Baseline** - Mark spec ready for implementation

**Follow this workflow** for every spec you develop.

---

### 3. [03-SPEC-PRODUCTION.md](./03-SPEC-PRODUCTION.md)
**Techniques for writing** high-quality OpenSpec specs.

**Covers**:
- Spec file structure and naming
- Writing requirements (SHALL vs MUST)
- Writing scenarios (Given/When/Then)
- Cross-referencing artifacts
- Documenting constraints
- Creating design.md (when needed)

**Reference this** when writing spec content.

---

### 4. [04-SPEC-VALIDATION.md](./04-SPEC-VALIDATION.md)
**Techniques for validating** spec quality and implementability.

**5 Validation Layers**:
1. **OpenSpec Format Validation** - openspec validate --strict
2. **Specification Coverage Validation** - All sections covered
3. **Technical Accuracy Validation** - Constraints accurate
4. **Implementability Validation** - Requirements specific, scenarios testable
5. **Traceability Validation** - All requirements traced to artifacts

**Use this** to validate specs before review.

---

### 5. [05-REQUIREMENTS-ANALYSIS.md](./05-REQUIREMENTS-ANALYSIS.md)
**How to approach, understand, and document** Lui-XML requirements.

**Covers**:
- Where requirements come from (specification, roadmap phases)
- Requirements analysis process
- Mapping requirements to scenarios
- Requirements tracking
- Common mistakes

**Use this** before starting any spec development.

---

### 6. [06-COMMON-PITFALLS.md](./06-COMMON-PITFALLS.md)
**Catalog of common mistakes** in spec development and how to avoid them.

**10 Common Pitfalls**:
1. Document completion delusion (focus on coverage, not word count)
2. Vague requirements (be specific with acceptance criteria)
3. Missing scenarios (every requirement needs scenarios)
4. Incomplete specification coverage (cover all sections)
5. Implementation details in requirements (separate requirements from design)
6. Untestable scenarios (make specific and verifiable)
7. Missing error scenarios (include error handling)
8. Contradictory requirements (check for conflicts)
9. Missing constraints (document all constraints)
10. Skipping traceability (always include source references)

**Review this** to avoid common mistakes.

---

### 7. [07-CHECKLISTS.md](./07-CHECKLISTS.md)
**Ready-to-use checklists** for ensuring process compliance.

**Checklists included**:
- Pre-spec development checklist
- Spec development progress checklist
- Spec completion checklist
- Spec review checklist
- Continuous spec review checklist
- Self-correction checklist
- Pre-implementation spec review checklist

**Print these** and use them for all spec development work.

---

## How to Use This Guide

### For New Spec Developers

1. **Read all 7 documents** in order before starting work
2. **Print the checklists** from 07-CHECKLISTS.md
3. **Start with 05-REQUIREMENTS-ANALYSIS.md** to understand requirements
4. **Follow 02-WORKFLOW.md** 7-phase process
5. **Reference 03-SPEC-PRODUCTION.md** when writing content
6. **Use 04-SPEC-VALIDATION.md** to validate your work
7. **Review 06-COMMON-PITFALLS.md** to avoid mistakes
8. **Use checklists from 07-CHECKLISTS.md** throughout

### For Experienced Spec Developers

1. **Review 01-PRINCIPLES.md** periodically
2. **Follow 02-WORKFLOW.md** for each spec
3. **Reference 03-SPEC-PRODUCTION.md** and 04-SPEC-VALIDATION.md** as needed
4. **Use checklists** before marking specs complete
5. **Review 06-COMMON-PITFALLS.md** when stuck

### For Spec Reviewers

1. **Use spec review checklist** from 07-CHECKLISTS.md
2. **Verify specification coverage** is 100%
3. **Verify implementability** of all requirements
4. **Verify traceability** is complete
5. **Don't approve** if checklist items are unchecked

---

## Critical Files to Read First

### Must Read (Before Starting Any Spec)

1. **[docs/planning/specifications/1/README.md](../../../planning/specifications/1/README.md)**
   - The authoritative source of technical requirements
   - Read sections relevant to your capability
   - Time: 1-2 hours for complete read

2. **[openspec/AGENTS.md](../../../../openspec/AGENTS.md)**
   - OpenSpec format, workflow, validation
   - Time: 30-60 minutes

3. **[openspec/project.md](../../../../openspec/project.md)**
   - Project context, tech stack, constraints
   - Time: 30-45 minutes

4. **[01-PRINCIPLES.md](./01-PRINCIPLES.md)** (This guide)
   - Spec development philosophy
   - Time: 30-45 minutes

5. **[02-WORKFLOW.md](./02-WORKFLOW.md)** (This guide)
   - Step-by-step workflow
   - Time: 45-60 minutes

### Reference as Needed

6. **Implementation Roadmap Phases** (from specification document)
   - Phase 1: Archaeology & Extraction (code extraction from LVGL)
   - Phase 2: Compatibility Engineering (shim layer implementation)
   - Phase 3: Build System Hardening (CMake/ESP-IDF integration)
   - Phase 4: Testing & Validation (unit tests, integration tests)
   - Phase 5: Documentation & Release (API docs, migration guides)

---

## Quick Start Path

**For those who want to start immediately** (not recommended, better to read full guide):

1. **Read**: 01-PRINCIPLES.md (30 min)
2. **Read**: 02-WORKFLOW.md phases 1-3 (30 min)
3. **Print**: 07-CHECKLISTS.md pre-development checklist
4. **Read**: Specification document sections for your capability (30-60 min)
5. **Read**: openspec/project.md (30 min)
6. **Start**: Follow 02-WORKFLOW.md 7-phase process

**Better approach**: Read all 7 documents first (2-3 hours total), then start.

---

## Spec Development Template

**For each spec you develop**, create:

```
openspec/specs/<capability>/
├── spec.md           # Requirements and scenarios
├── design.md         # Technical decisions (if needed)
├── traceability.md   # Traceability matrix
└── BASELINE.md       # Baseline document (when complete)
```

**Use the spec template** from existing specs or create new following OpenSpec format.

---

## Success Criteria

### Spec Development Complete When:

- [ ] All 7 development phases complete (from 02-WORKFLOW.md)
- [ ] All specification sections covered (100%)
- [ ] All roadmap phases addressed (if applicable)
- [ ] openspec validate --strict passes
- [ ] All requirements implementable
- [ ] All scenarios testable
- [ ] Traceability complete
- [ ] Peer review approved
- [ ] Spec baselined

### Overall Success:

- [ ] Specs are implementable (not vague)
- [ ] Specs align with specification document
- [ ] Specs align with implementation roadmap
- [ ] Dependencies between specs are clear
- [ ] Implementation can proceed from specs

---

## Common Questions

### Q: Can I skip reading the specification?
**A**: NO. The specification document is the PRIMARY source of requirements. You MUST read it.

### Q: Can I write specs from implementation tasks?
**A**: NO. Requirements come from the specification document and roadmap, not implementation tasks.

### Q: Can I write vague requirements?
**A**: NO. Requirements must be specific and testable. See 03-SPEC-PRODUCTION.md.

### Q: Can I skip scenarios?
**A**: NO. Every requirement MUST have at least one scenario. See 06-COMMON-PITFALLS.md.

### Q: What if I find a contradiction in the specification?
**A**: Document it in design.md under "Open Questions" and flag for review.

### Q: What if a requirement is unimplementable?
**A**: Document the issue, propose alternatives, and flag for review.

---

## Support and Feedback

### If You Need Help

1. **Re-read the relevant guide document**
2. **Check the checklists** in 07-CHECKLISTS.md
3. **Review common pitfalls** in 06-COMMON-PITFALLS.md
4. **Ask for peer review**
5. **Consult the specification** again

### Providing Feedback

If you find issues with this guide:
1. Document what's unclear or missing
2. Propose improvements
3. Discuss with team
4. Update in version control
5. Communicate changes

---

## Summary

**This guide is your foundation for successful spec development.**

**Key points**:
1. Read all 7 documents before starting
2. Follow the 7-phase workflow
3. Focus on specification coverage, not document completion
4. Write specific requirements with testable scenarios
5. Validate continuously
6. Use the checklists
7. Never skip steps

**Following this guide will prevent spec development failures.**

**Use it consistently.**

---

**Next**: Start with [01-PRINCIPLES.md](./01-PRINCIPLES.md) to understand the philosophy.
