# Spec Validation for Lui-XML

**Purpose**: Techniques for validating spec quality and implementability.

**Key Principle**: Success = implementable spec, NOT passing format validation.

---

## The Validation Imperative

### What We Must Avoid

**Wrong approach**:
- ✅ openspec validate --strict passes
- ✅ All requirements have scenarios
- ✅ Spec is 5000 words
- ❌ Requirements are vague
- ❌ Scenarios are untestable
- ❌ Specification coverage incomplete

**Right approach** (for Lui-XML):
- ✅ Specification coverage 100%
- ✅ All requirements implementable
- ✅ All scenarios testable
- ✅ Traceability complete
- ✅ Implementation-ready

---

## Validation Layers

### Layer 1: OpenSpec Format Validation

**Purpose**: Verify spec follows OpenSpec conventions

**Command**:
```bash
openspec validate <spec-id> --strict
```

**What it checks**:
- Spec file exists at correct location
- All requirements use ### headers
- All scenarios use #### headers
- All scenarios use Given/When/Then format
- No missing sections

---

### Layer 2: Specification Coverage Validation

**Purpose**: Verify all specification requirements are covered

**Create coverage matrix**:
```markdown
### Specification Coverage Matrix

| Specification Section | Key Requirements | Mapped Requirement | Status |
|----------------------|------------------|-------------------|--------|
| Section 3.2 | Namespace isolation | Namespace Isolation | ✅ |
| Section 4.2 | CMake integration | Build System Integration | ✅ |

**Coverage**: 100%
```

---

### Layer 3: Technical Accuracy Validation

**Purpose**: Verify technical details are correct

**Check each requirement for technical accuracy**:
- [ ] Constraints are realistic (LVGL version, memory, namespace)
- [ ] Dependencies are correct (LVGL target, CMake, ESP-IDF)
- [ ] Resource requirements specified
- [ ] Legal constraints documented (MIT license, provenance)

---

### Layer 4: Implementability Validation

**Purpose**: Verify requirements are implementable, not vague

**Implementability checklist**:
- [ ] Is specific (not "system shall parse XML")
- [ ] Is testable (has verifiable scenarios)
- [ ] Has no contradictions
- [ ] Has no undefined terms
- [ ] Has clear acceptance criteria
- [ ] Has no implementation details

**Examples of unimplementable requirements**:

❌ **UNIMPLEMENTABLE**:
```markdown
### Requirement: XML Support
The system SHALL provide XML support.

**Problems**:
- "XML support" is vague - parse? generate? validate?
- No acceptance criteria
- No testable scenarios
```

✅ **IMPLEMENTABLE**:
```markdown
### Requirement: XML Parser
The system SHALL parse LVGL XML markup using lui_xml_load() and create
corresponding LVGL widgets with the lui_ namespace prefix.

**Acceptance**:
- Parses valid XML markup
- Creates LVGL objects
- Returns LUI_XML_OK on success
```

---

### Layer 5: Traceability Validation

**Purpose**: Verify all requirements trace to artifacts

**Traceability matrix**:
```markdown
### Traceability Validation

**Specification → Requirements**:
- [ ] Every specification section maps to ≥1 requirement
- [ ] No orphaned specification sections

**Roadmap → Requirements**:
- [ ] Every phase maps to ≥1 requirement
- [ ] All phase deliverables addressed

**Requirements → Artifacts**:
- [ ] Every requirement maps to specification section
- [ ] Every requirement maps to roadmap phase
- [ ] No orphaned requirements
```

---

## Validation Process

### Step-by-Step Validation

**Step 1: OpenSpec Format Validation**
```bash
openspec validate <spec-id> --strict
```

**Step 2: Specification Coverage**
- Create coverage matrix
- Verify all sections mapped
- No orphaned sections

**Step 3: Technical Accuracy**
- Verify constraints are realistic
- Verify dependencies are correct
- Verify resource requirements specified

**Step 4: Implementability**
- Verify requirements are specific
- Verify scenarios are testable
- Check for contradictions

**Step 5: Traceability**
- Create traceability matrix
- Verify all artifacts covered
- Verify no orphaned requirements

**Step 6: Peer Review**
- Self-review complete
- Peer review requested
- Feedback incorporated

---

## Validation Checklist

### For Each Requirement

- [ ] Uses SHALL/MUST (not should/may)
- [ ] Is specific (not vague)
- [ ] Is testable (has scenarios)
- [ ] Has specification reference
- [ ] Has roadmap phase reference
- [ ] Has constraints documented
- [ ] No implementation details
- [ ] No contradictions

### For Each Scenario

- [ ] Uses #### Scenario: header
- [ ] Uses Given/When/Then format
- [ ] Has specific conditions
- [ ] Has verifiable outcomes
- [ ] Is testable
- [ ] Covers success case
- [ ] Covers error cases (if applicable)

### For Spec as a Whole

- [ ] openspec validate --strict passes
- [ ] Specification coverage 100%
- [ ] All roadmap phases addressed
- [ ] All requirements implementable
- [ ] All scenarios testable
- [ ] Traceability complete
- [ ] No contradictions
- [ ] Technical details accurate

---

## Common Validation Issues

### Issue 1: Vague Requirements

**Fix**: Make specific with acceptance criteria
```markdown
❌ The system SHALL parse XML.

✅ The system SHALL parse LVGL XML markup and create widgets using lui_xml_load().
```

### Issue 2: Untestable Scenarios

**Fix**: Make specific with verifiable outcomes
```markdown
❌ Scenario: Parse
- **WHEN** parsing XML
- **THEN** it works well

✅ Scenario: Successful Parse
- **WHEN** lui_xml_load() is called with valid XML
- **THEN** returns LUI_XML_OK
- **AND** creates LVGL objects
```

### Issue 3: Missing Specification Coverage

**Fix**: Add requirement to cover section

---

## Summary

**Validation is NOT optional.**

**Minimum validation**:
1. OpenSpec format validation
2. Specification coverage check
3. Implementability review

**Better validation**:
4. Technical accuracy check
5. Traceability verification
6. Scenario testability review

**Best validation**:
7. Peer review
8. Implementation team review

**Success = implementable spec, not just valid format.**

---

**Next**: See [05-REQUIREMENTS-ANALYSIS.md](./05-REQUIREMENTS-ANALYSIS.md) for requirements analysis techniques.
