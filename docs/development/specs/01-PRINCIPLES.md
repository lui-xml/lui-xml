# Core Principles of Spec Development

**Purpose**: The foundational principles that guide all spec development work for the Lui-XML project.

**Status**: NON-NEGOTIABLE - These principles must be followed for all spec development work.

---

## The Core Principle

**Focus on SPECIFICATION COVERAGE and IMPLEMENTABILITY, not document completion metrics.**

### What This Means

**Wrong Mindset** (leads to incomplete specs):
- "I completed all the spec sections"
- "All requirements have scenarios"
- "The spec document is 5000 words"
- "I can mark this spec complete"

**Right Mindset** (leads to implementable specs):
- "Every specification requirement is covered"
- "All scenarios are testable"
- "Every requirement is implementable (not vague)"
- "The spec aligns with the implementation roadmap"

### Why This Matters

From our context as a community-maintained extension library:
- Specs are often treated as documentation exercises
- Requirements are vague or untestable
- Critical constraints are missing
- **Implementation teams cannot implement from vague specs**

**Spec completeness metrics can be deceptive. Real coverage matters.**

---

## Principle 1: Specification First, Implementation Later

### The Principle

**Never write spec requirements until you understand the specification document.**

### What Went Wrong

```
1. Read implementation roadmap or tasks
2. Start writing spec requirements immediately
3. Create scenarios with generic acceptance criteria
4. Mark spec complete
5. Never verify against specification
```

### What You Should Do

```
1. Read specification document sections
2. Read implementation roadmap phases
3. Extract requirements from specification
4. Write scenarios using Given/When/Then format
5. Map requirements to roadmap phases
6. Verify specification coverage
7. Only then mark spec complete
```

### Application Checklist

Before starting ANY spec development:

- [ ] Have I read the relevant specification sections?
- [ ] Have I read the related roadmap phases?
- [ ] Do I understand the technical constraints?
- [ ] Do I understand the success criteria?
- [ ] Have I documented specification requirements?

**Only proceed when ALL checked.**

### Key Insight

Requirements come from the specification document and implementation roadmap.

- Specification defines WHAT the system must do
- Roadmap defines HOW it will be implemented
- **Specs formalize requirements with testable scenarios**

**Read specification first. Implementation roadmap second.**

---

## Principle 2: Scenarios First

### The Principle

**Every requirement MUST have at least one testable scenario.**

### The Anti-Pattern

❌ **WRONG**: Requirements without scenarios
```markdown
### Requirement: XML Parser
The system SHALL support XML parsing for LVGL UI definitions.

**Implementation**: Parser module needed
```

**Problems**:
- No way to test if requirement is met
- No specific behavior defined
- Implementation team cannot determine what's needed

### The Correct Pattern

✅ **RIGHT**: Requirements with scenarios
```markdown
### Requirement: XML Parser Initialization
The system SHALL initialize the XML parser during library startup and register
default widget parsers (button, label, image) with the `lui_xml` namespace.

#### Scenario: Parser Initialization
- **GIVEN** Lui-XML library is loaded
- **WHEN** lui_xml_create() is called
- **THEN** an XML parser instance is created
- **AND** default widget parsers are registered (luixml_button, luixml_label, luixml_image)
- **AND** the parser returns LUI_XML_OK
```

**Benefit**: Requirement is testable and implementable.

### Scenario Hierarchy

**Level 1: Primary Scenarios** (REQUIRED)
- **Purpose**: Validate core requirement functionality
- **Format**: Given/When/Then with specific conditions
- **Quantity**: At least one per requirement
- **Priority**: Highest - write these FIRST

**Level 2: Edge Case Scenarios** (IMPORTANT)
- **Purpose**: Validate boundary conditions and error cases
- **Format**: Given/When/Then for error conditions
- **Quantity**: As needed for completeness
- **Priority**: High - write these SECOND

**Level 3: Integration Scenarios** (NICE TO HAVE)
- **Purpose**: Validate interaction between requirements
- **Format**: End-to-end scenarios
- **Quantity**: As needed for complex features
- **Priority**: Medium - write these LAST

### Key Insight

**Requirements without scenarios are untestable.**

If a requirement has no scenarios:
- Implementation team doesn't know what to build
- Testing team doesn't know what to verify
- Spec reviewers cannot validate completeness

**Write scenarios for every requirement.**

---

## Principle 3: Spec Validation, Not Document Metrics

### The Principle

**Success = implementable spec, NOT word count or scenario count.**

### The Deception

**What is claimed** (but is WRONG):
- "50 requirements written ✅"
- "100 scenarios defined ✅"
- "Spec is 5000 words ✅"

**Reality**:
- Requirements are vague
- Scenarios are untestable
- Spec doesn't align with specification
- **Implementation cannot proceed**

### The New Validation Approach

**Validation Layer 1: OpenSpec Format Validation**
```bash
openspec validate <spec-id> --strict
```
- Verifies spec follows OpenSpec format
- Checks all requirements have scenarios
- Validates scenario syntax (Given/When/Then)

**Validation Layer 2: Specification Coverage**
```markdown
### Specification Section Coverage
- [ ] Section 2: Background & Problem → Requirement: Namespace Isolation
- [ ] Section 3: Proposed Solution → Requirement: Satellite Architecture
- [ ] Section 4: Technical Specification → Requirement: Build System Integration
```
- Maps every specification section to requirements
- Ensures no specification requirement is missed

**Validation Layer 3: Technical Accuracy**
```markdown
### Technical Validation
- [ ] Constraints documented (memory, LVGL version, namespace)
- [ ] Dependencies identified (LVGL target, CMake, ESP-IDF)
- [ ] Technical feasibility verified
- [ ] Resource requirements specified
```

**Validation Layer 4: Implementability**
```markdown
### Implementability Check
- [ ] Requirements are specific (not "system shall parse XML")
- [ ] Scenarios are testable (not "works well")
- [ ] No contradictions between requirements
- [ ] No undefined terms or ambiguity
```

**Validation Layer 5: Traceability**
```markdown
### Traceability Matrix
- [ ] All requirements trace to specification sections
- [ ] All requirements trace to roadmap phases
- [ ] All scenarios map to acceptance criteria
```

### New Success Metrics

**OLD Metrics (Deceptive)**:
- Requirements: 50 ✅
- Scenarios: 100 ✅
- Word count: 5000 ✅

**NEW Metrics (Honest)**:
- Specification coverage: 100% ✅
- Requirements implementable: 50/50 ✅
- Scenarios testable: 100/100 ✅
- Traceability complete: 100% ✅

### Key Insight

**Document metrics measure spec size, not spec quality.**

5000 words with vague requirements ≠ implementable spec
1000 words with specific requirements = implementable spec

**Validate specification coverage and implementability, not word count.**

---

## Principle 4: Follow OpenSpec Format, Don't Invent

### The Principle

**When writing specs, follow OpenSpec format EXACTLY.**

### What Went Wrong

Created a NEW format without checking OpenSpec conventions:
```markdown
// My invented format
## Feature: XML Parser
- Description: This feature parses XML
- Priority: High
- Tasks:
  - Implement parser
  - Test parser
```

**Problems**:
- Doesn't follow OpenSpec spec.md format
- Missing SHALL/MUST requirements
- Missing scenario format (Given/When/Then)
- Cannot be validated with `openspec validate`

### The Correct Approach

**Step 1: Read OpenSpec Format Documentation**
```bash
cat openspec/AGENTS.md
```

**Step 2: Read Existing Spec Examples**
```bash
# Find existing specs
find openspec/specs -name "spec.md"

# Read example
cat openspec/specs/<capability>/spec.md
```

**Step 3: Follow Format Exactly**
```markdown
### Requirement: Namespace Isolation
The system SHALL use `lui_` prefix for all public APIs and `luixml_` prefix
for internal widget bindings to prevent collision with LVGL symbols.

#### Scenario: Symbol Registration
- **GIVEN** Lui-XML library is initializing
- **WHEN** registering widget parsers
- **THEN** all internal symbols use luixml_ prefix
- **AND** all public APIs use lui_ prefix
- **AND** no symbols use lv_xml_ prefix
```

**Step 4: Only Deviate With Explicit Justification**
```markdown
## Format Deviation Request

Standard format: SHALL/MUST with Given/When/Then
Proposed format: [NONE - follow standard format]

Decision: FOLLOW OPENSPEC FORMAT
```

### Format Checklist

**Before creating spec content**:
- [ ] Have I read OpenSpec AGENTS.md?
- [ ] Have I read existing spec examples?
- [ ] Do I understand SHALL vs MUST vs MAY?
- [ ] Do I understand scenario format (Given/When/Then)?
- [ ] Do I have a DAMN GOOD REASON to deviate?

**After creating spec content**:
- [ ] Does my spec use ### for Requirement headers?
- [ ] Does my spec use #### for Scenario headers?
- [ ] Do all requirements use SHALL/MUST?
- [ ] Do all scenarios use GIVEN/WHEN/THEN?
- [ ] Can `openspec validate --strict` pass?

### Key Insight

**Inventing formats without checking OpenSpec breaks validation.**

Your "simplified" format might seem cleaner, but if it doesn't follow OpenSpec conventions, it cannot be validated.

**Follow OpenSpec format exactly.**

---

## Principle 5: Spec Completeness ≠ Coverage

### The Principle

**Marking a spec complete requires validating SPECIFICATION COVERAGE, not just writing requirements.**

### Old Definition of "Done" (WRONG)

```markdown
Spec: XML Parser

My checklist:
- [x] 50 requirements written
- [x] 100 scenarios defined
- [x] Spec is 5000 words
- [x] Spec follows OpenSpec format

Status: COMPLETE ✅
```

**Problem**: Never checked if all specification sections are covered

### New Definition of "Done"

```markdown
Spec: XML Parser

Specification coverage checklist:
- [ ] Section 2: Background & Problem Statement
- [ ] Section 3: Proposed Solution (Lui Architecture)
- [ ] Section 4: Technical Specification
- [ ] Section 5: Implementation Roadmap

Requirements checklist:
- [x] 50 requirements written
- [x] 100 scenarios defined
- [x] Spec follows OpenSpec format

Traceability checklist:
- [ ] All requirements map to specification sections
- [ ] All requirements map to roadmap phases
- [ ] All scenarios map to acceptance criteria

Validation checklist:
- [ ] openspec validate --strict passes
- [ ] Specification coverage 100%
- [ ] All requirements implementable
- [ ] All scenarios testable

Status: INCOMPLETE ❌ (traceability pending)
```

### Spec Completion Process

**Phase 1: Requirements Extraction**
1. Read specification sections
2. Extract requirements
3. Document constraints
4. Write draft requirements

**Phase 2: Scenario Development**
1. Write scenarios for each requirement
2. Use Given/When/Then format
3. Ensure testability
4. Validate with openspec validate --strict

**Phase 3: Traceability**
1. Map requirements to specification sections
2. Map requirements to roadmap phases
3. Document all mappings
4. Create traceability matrix

**Phase 4: Validation**
1. Run openspec validate --strict
2. Verify specification coverage 100%
3. Verify implementability
4. Peer review

**Phase 5: Baseline**
1. Final validation
2. Mark spec as baselined
3. Ready for implementation

### Key Insight

**Writing requirements ≠ satisfying specification coverage.**

You can write perfect requirements that miss critical specification sections.

**Validate specification coverage before marking done.**

---

## Principle 6: Continuous Review

### The Principle

**Review spec quality continuously against specification, not just at the end.**

### Old Process (BROKEN)

```
Extract requirements
  ↓
Write scenarios
  ↓
Validate format
  ↓
Mark complete ✅
  ↓
NEVER VERIFY SPECIFICATION COVERAGE
```

### New Process (CORRECT)

```
Extract requirements
  ↓
Verify specification coverage (all sections addressed)
  ↓
Write scenarios
  ↓
Validate specification coverage (scenarios address requirements)
  ↓
Validate format
  ↓
Verify traceability (specification → requirements → scenarios)
  ↓
FINAL VALIDATION (specification coverage 100%, format valid, implementable)
  ↓
Mark complete ✅
```

### Continuous Review Script

Create a review script for your spec development:

```python
#!/usr/bin/env python3
"""
Continuous spec review script for Lui-XML.

Run this after EVERY spec change.
"""

import sys
from pathlib import Path

def run_review():
    """Run all review checks."""

    print("=" * 60)
    print("CONTINUOUS SPEC REVIEW - Lui-XML")
    print("=" * 60)

    checks = []

    # Check 1: Specification file exists
    spec_doc = Path("docs/planning/specifications/1/README.md")
    if spec_doc.exists():
        print(f"✅ Specification document found")
        checks.append(True)
    else:
        print(f"❌ Specification document NOT found")
        checks.append(False)

    # Check 2: Spec file exists
    spec_file = Path("openspec/specs/<capability>/spec.md")
    if spec_file.exists():
        print(f"✅ Spec file exists")
        checks.append(True)
    else:
        print(f"❌ Spec file NOT found")
        checks.append(False)

    # Check 3: Requirements have scenarios
    # Check 4: Specification coverage
    # Check 5: Traceability exists

    # Summary
    print("\n" + "=" * 60)
    passed = sum(checks)
    total = len(checks)
    print(f"REVIEW: {passed}/{total} checks passed")
    print("=" * 60)

    if passed == total:
        print("✅ ALL CHECKS PASSED")
        return 0
    else:
        print("❌ SOME CHECKS FAILED")
        return 1

if __name__ == "__main__":
    sys.exit(run_review())
```

**Usage**:
```bash
# After every spec change
python scripts/review_spec_continuous.py
```

### Key Insight

**Batching review until the end misses problems.**

If you wait until all requirements are written to review specification coverage:
- You won't know which requirements are missing
- You might miss entire specification sections
- You might need to rewrite large sections

**Review after every change.**

---

## Summary: The 6 Principles

1. **Specification First** - Understand before writing
2. **Scenarios First** - Every requirement needs scenarios
3. **Spec Validation** - Implementable specs, not word count
4. **Follow OpenSpec Format** - Don't invent without checking
5. **Spec Completeness ≠ Coverage** - Validate specification coverage
6. **Continuous Review** - Review against specification continuously

## Self-Correction Checklist

**Before claiming spec is complete, ask:**

- [ ] Did I read all relevant specification sections?
- [ ] Did I read the relevant roadmap phases?
- [ ] Did I write scenarios for every requirement?
- [ ] Did I validate with openspec validate --strict?
- [ ] Did I verify specification coverage is 100%?
- [ ] Did I map requirements to specification sections?
- [ ] Can implementation team build from this spec?

**If ANY answer is NO, the spec is NOT complete.**

---

**Next**: See [02-WORKFLOW.md](./02-WORKFLOW.md) for the step-by-step spec development workflow.
