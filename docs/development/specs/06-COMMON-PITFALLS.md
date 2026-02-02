# Common Spec Development Pitfalls

**Purpose**: Catalog of common mistakes in spec development and how to avoid them.

**Key Benefit**: Learn from others' mistakes so you don't repeat them.

---

## Pitfall 1: The Document Completion Delusion

### What It Is

Focusing on completing spec document rather than ensuring specification coverage and implementability.

### Symptoms

- Marking spec complete when all requirements are written
- Claiming success when scenarios are defined
- Measuring progress by word count or requirement count
- Ignoring whether spec is implementable

### How to Avoid

**Focus on specification coverage and implementability**:
```markdown
## Wrong Approach
Spec: XML Parser
- [x] 50 requirements written
- [x] 100 scenarios defined
Status: COMPLETE ✅

## Correct Approach
Spec: XML Parser

Specification coverage:
- [ ] Section 3.2: Namespace → covered
- [ ] Section 4.1: Parser → covered

Implementability:
- [ ] All requirements specific
- [ ] All scenarios testable

Validation:
- [x] openspec validate --strict passes
- [x] Specification coverage 100%

Status: COMPLETE ✅
```

**Rule**: Spec complete only when specification coverage 100% and implementable.

---

## Pitfall 2: Vague Requirements Delusion

### What It Is

Writing vague requirements that cannot be implemented or tested.

### Symptoms

- Requirements like "system shall parse XML"
- Requirements like "system shall be fast"
- No specific acceptance criteria

### How to Avoid

**Always be specific with acceptance criteria**:
```markdown
❌ WRONG: Vague requirement
### Requirement: XML Support
The system SHALL support XML.

✅ CORRECT: Specific requirement
### Requirement: XML Parser
The system SHALL parse LVGL XML markup using lui_xml_load() and create
corresponding LVGL widgets with the lui_ namespace prefix.
```

**Rule**: Every requirement must be specific and testable.

---

## Pitfall 3: Missing Scenarios

### What It Is

Writing requirements without scenarios, or scenarios that are untestable.

### Symptoms

- Requirements with no scenarios
- Scenarios like "it works"
- Scenarios with no verifiable outcomes

### How to Avoid

**Every requirement MUST have at least one scenario**:
```markdown
❌ WRONG: No scenarios
### Requirement: Parser
The system SHALL parse XML.

✅ CORRECT: With scenarios
### Requirement: XML Parser
The system SHALL parse LVGL XML markup.

#### Scenario: Successful Parse
- **GIVEN** valid XML markup is provided
- **WHEN** lui_xml_load() is called
- **THEN** LVGL widgets are created
- **AND** returns LUI_XML_OK
```

**Rule**: No scenarios = incomplete requirement.

---

## Pitfall 4: Incomplete Specification Coverage

### What It Is

Writing spec requirements without covering all specification sections.

### Symptoms

- Specification sections with no corresponding requirements
- Implicit requirements not captured
- Constraints not documented

### How to Avoid

**Create specification coverage matrix**:
```markdown
### Specification Coverage

| Section | Key Requirements | Mapped Requirement | Status |
|---------|------------------|-------------------|--------|
| 3.2 | Namespace isolation | Namespace Isolation | ✅ |
| 4.2 | Build system | CMake Integration | ✅ |

**Coverage**: 100%
```

**Rule**: Every specification section needs at least one requirement.

---

## Pitfall 5: Implementation Details in Requirements

### What It Is

Writing implementation details instead of requirements.

### Symptoms

- Requirements mention specific function names
- Requirements specify file paths
- Requirements define code structure

### How to Avoid

**Separate requirements from implementation**:
```markdown
❌ WRONG: Implementation details
### Requirement: Build System
The system SHALL call find_package(LVGL REQUIRED).

✅ CORRECT: Requirement only
### Requirement: LVGL Dependency Detection
The system SHALL detect and link against an existing LVGL target provided
by the user project.

**Note**: CMake implementation details go in design.md
```

**Rule**: Requirements specify what, design specifies how.

---

## Pitfall 6: Untestable Scenarios

### What It Is

Writing scenarios that cannot be tested or verified.

### Symptoms

- Scenarios with subjective outcomes ("works well")
- Scenarios with no specific conditions
- Scenarios with no verifiable outcomes

### How to Avoid

**Make scenarios specific and verifiable**:
```markdown
❌ WRONG: Untestable
#### Scenario: Parser Works
- **WHEN** parsing XML
- **THEN** it works well

✅ CORRECT: Testable
#### Scenario: Successful XML Parse
- **GIVEN** valid XML markup is provided
- **WHEN** lui_xml_load() is called
- **THEN** creates LVGL button widget
- **AND** returns LUI_XML_OK
```

**Rule**: Every scenario must be objectively testable.

---

## Pitfall 7: Missing Error Scenarios

### What It Is

Only writing success scenarios, ignoring error conditions.

### Symptoms

- Requirements with only success scenarios
- No error handling specified
- No edge cases covered

### How to Avoid

**Include error scenarios for all error conditions**:
```markdown
❌ WRONG: Only success
#### Scenario: Parse Success
- **WHEN** parsing XML
- **THEN** succeeds

✅ CORRECT: Success + Error
#### Scenario: Parse Success
- **GIVEN** valid XML is provided
- **WHEN** lui_xml_load() is called
- **THEN** creates widgets and returns LUI_XML_OK

#### Scenario: Parse Error
- **GIVEN** XML has syntax error
- **WHEN** lui_xml_load() is called
- **THEN** returns LUI_XML_ERROR_SYNTAX
- **AND** reports error location
```

**Rule**: Every requirement needs error scenarios.

---

## Pitfall 8: Contradictory Requirements

### What It Is

Writing requirements that contradict each other.

### Symptoms

- Two requirements with conflicting constraints
- Performance requirements that cannot be met
- Resource constraints that conflict

### How to Avoid

**Check for contradictions**:
```markdown
❌ WRONG: Contradictory
Requirement A: Parse within 1 second
Requirement B: Must validate against XSD schema

**Contradiction**: XSD validation takes 2-3 seconds on target hardware

✅ CORRECT: Consistent
Requirement A: Parse within 5 seconds
Requirement B: Must validate against XSD schema

**Resolution**: 5 seconds allows for XSD validation (2-3s)
plus parsing overhead (1-2s)
```

**Rule**: Run contradiction detection before marking spec complete.

---

## Pitfall 9: Missing Constraints

### What It Is

Not documenting constraints from the specification.

### Symptoms

- No performance constraints
- No memory constraints
- No legal constraints (MIT, provenance)

### How to Avoid

**Always document constraints**:
```markdown
❌ WRONG: No constraints
### Requirement: Parser
The system SHALL parse XML.

✅ CORRECT: With constraints
### Requirement: XML Parser
The system SHALL parse LVGL XML markup within 2 seconds using ≤ 4 KB heap.

**Performance**: ≤ 2 seconds on ESP32-C3
**Memory**: ≤ 4 KB heap during parsing
**Legal**: Preserve git authorship, MIT license
```

**Rule**: Every requirement needs constraints documented.

---

## Pitfall 10: Skipping Traceability

### What It Is

Not mapping requirements to specification and roadmap.

### Symptoms

- Requirements with no references
- No way to trace requirement to source
- Cannot verify specification coverage

### How to Avoid

**Always include traceability**:
```markdown
❌ WRONG: No traceability
### Requirement: Parser
The system SHALL parse XML.

✅ CORRECT: With traceability
### Requirement: XML Parser
The system SHALL parse LVGL XML markup.

**Specification Reference**: Section 4.1 (Technical Specification)
**Roadmap Phase**: Phase 2 (Compatibility Engineering)
```

**Rule**: Every requirement needs source references.

---

## Warning Signs

### You Might Be Falling Into a Pitfall If:

- Requirements are vague ("system shall parse XML")
- Scenarios untestable ("it works well")
- Specification sections not covered
- No error scenarios
- Implementation details in requirements
- No constraints documented
- No traceability to sources
- Contradictions between requirements

**If any of these apply**: Stop and reassess approach.

---

## Prevention Checklist

**Before starting spec development**:
- [ ] Read all specification sections
- [ ] Read all roadmap phases
- [ ] Document requirements from sources
- [ ] Create coverage matrix

**During spec development**:
- [ ] Requirements specific (not vague)
- [ ] Scenarios testable (not subjective)
- [ ] Including error scenarios
- [ ] Documenting constraints
- [ ] Adding traceability

**Before marking complete**:
- [ ] Specification coverage 100%
- [ ] All requirements implementable
- [ ] All scenarios testable
- [ ] No contradictions
- [ ] Traceability complete
- [ ] Peer review approved

**If ANY unchecked**: Spec is not complete.

---

## Summary

**These pitfalls are common, avoidable, and dangerous.**

**Key prevention strategies**:
1. Focus on specification coverage, not document completion
2. Be specific, not vague
3. Every requirement needs testable scenarios
4. Cover all specification sections
5. Separate requirements from implementation
6. Make scenarios testable
7. Include error scenarios
8. Check for contradictions
9. Document constraints
10. Always include traceability

**Be vigilant. Check yourself against this list regularly.**

---

**Next**: See [07-CHECKLISTS.md](./07-CHECKLISTS.md) for ready-to-use checklists.
