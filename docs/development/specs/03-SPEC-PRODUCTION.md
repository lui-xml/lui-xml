# Spec Production for Lui-XML

**Purpose**: Techniques for writing high-quality OpenSpec specs.

**Key Principle**: Specs are implementable requirements, not documentation exercises.

---

## The Spec Production Imperative

### What We Must Avoid

**Wrong approach**:
- ✅ 5000 words written
- ✅ 50 requirements documented
- ✅ 100 scenarios defined
- ❌ Requirements are vague
- ❌ Scenarios are untestable
- ❌ Implementation cannot proceed

**Right approach** (for Lui-XML):
- ✅ Specification coverage 100%
- ✅ All requirements implementable
- ✅ All scenarios testable
- ✅ Traceability complete
- ✅ Implementation team can build from spec

---

## Spec File Structure

### Location and Naming

**Location**: `openspec/specs/<capability>/spec.md`

**Capability naming**:
- Use kebab-case: `xml-parser`, `build-system`, `compatibility-layer`
- Single purpose per capability
- 10-minute understandability rule
- Split if description needs "AND"

### File Structure

```markdown
# [Capability Name]

## Purpose
[What this capability provides and why it matters - 2-3 sentences]

## Scope
- **Included**: [specific features]
- **Excluded**: [explicitly out of scope]

## Dependencies
- **Required specs**: [list of capability names]
- **Required components**: [LVGL, CMake, ESP-IDF]

## Requirements

### Requirement: [Requirement Name]
The system SHALL [complete requirement].

**Specification Reference**: Section X.Y
**Roadmap Phase**: Phase N

#### Scenario: [Scenario Name]
- **GIVEN** [precondition]
- **WHEN** [action]
- **THEN** [expected outcome]
- **AND** [additional conditions as needed]

## Constraints
- **Technical**: [LVGL version, namespace requirements]
- **Resource**: [memory constraints]
- **Legal**: [MIT license, provenance requirements]

## Out of Scope
- [explicitly excluded features]
```

---

## Writing Requirements

### Requirement Wording

**Use SHALL/MUST for normative requirements**:

✅ **CORRECT**:
```markdown
### Requirement: Namespace Isolation
The system SHALL use `lui_` prefix for all public APIs and `luixml_` prefix
for internal widget bindings to prevent collision with LVGL symbols.
```

❌ **WRONG**:
```markdown
### Requirement: Namespace
The system should use different prefixes.
```

**Why**: "Should" is non-normative. "Different prefixes" is vague.

### Requirement Specificity

**Be specific, not vague**:

❌ **VAGUE**:
```markdown
### Requirement: XML Support
The system SHALL support XML parsing.
```

✅ **SPECIFIC**:
```markdown
### Requirement: XML Parser Initialization
The system SHALL initialize the XML parser using lui_xml_create() and register
widget parsers for button, label, and image with the luixml_ namespace prefix.
```

### Common Requirement Mistakes

**Mistake 1: Implementation Details**

❌ **WRONG**:
```markdown
The system SHALL call cmake_minimum_required(VERSION 3.15).
```

✅ **CORRECT**:
```markdown
The system SHALL support CMake 3.15 or later for build configuration.
```

**Mistake 2: Vague Performance**

❌ **WRONG**:
```markdown
The system SHALL parse XML quickly.
```

✅ **CORRECT**:
```markdown
The system SHALL parse a 1000-line XML file within 2 seconds on ESP32-C3.
```

---

## Writing Scenarios

### Scenario Format

**Use Given/When/Then format**:

✅ **CORRECT**:
```markdown
#### Scenario: Parser Initialization
- **GIVEN** Lui-XML library is loaded
- **WHEN** lui_xml_create() is called
- **THEN** an XML parser instance is created
- **AND** default widget parsers are registered
- **AND** the parser returns LUI_XML_OK
```

❌ **WRONG**:
```markdown
#### Scenario: Parser
When create() is called, parser is created.
```

### Scenario Testability

**Scenarios must be testable**:

✅ **TESTABLE**:
```markdown
#### Scenario: Successful Widget Registration
- **GIVEN** XML parser is initialized
- **WHEN** lui_xml_register_widget() is called for "button"
- **THEN** luixml_button parser is registered
- **AND** returns LUI_XML_OK
```

❌ **UNTESTABLE**:
```markdown
#### Scenario: Widget Registration
- **WHEN** registering widget
- **THEN** it works well
```

### Error Scenarios

**Include error scenarios for robustness**:

```markdown
#### Scenario: Invalid XML Syntax
- **GIVEN** XML string contains malformed syntax
- **WHEN** lui_xml_load() is called
- **THEN** parser returns LUI_XML_ERROR_SYNTAX
- **AND** error position is reported
```

---

## Creating design.md

### When to Create design.md

**Create design.md if**:
- Cross-cutting change (multiple specs interact)
- New external dependency
- Significant data model changes
- Security, legal, or complexity implications

**Do NOT create design.md if**:
- Spec is straightforward
- No technical decisions needed
- Single self-contained capability

### design.md Structure

```markdown
## Context
[Background, constraints, stakeholders]

## Goals / Non-Goals
- Goals: [...]
- Non-Goals: [...]

## Decisions
- Decision: [What and why]
- Alternatives considered: [Options + rationale]

## Risks / Trade-offs
- [Risk] → Mitigation

## Open Questions
- [Question] → [Proposed answer]
```

---

## Spec Production Checklist

### Before Starting Spec Production

- [ ] Read all relevant specification sections
- [ ] Read roadmap phases
- [ ] Document requirements from specification
- [ ] Understand technical constraints
- [ ] Review OpenSpec format (AGENTS.md)

### During Spec Production

- [ ] All requirements use SHALL/MUST
- [ ] All requirements are specific (not vague)
- [ ] All requirements have at least one scenario
- [ ] All scenarios use Given/When/Then
- [ ] All scenarios are testable
- [ ] Specification references included
- [ ] Constraints documented
- [ ] Dependencies documented

### Before Submitting for Review

- [ ] Run openspec validate --strict (must pass)
- [ ] Verify specification coverage 100%
- [ ] Verify all requirements implementable
- [ ] Verify all scenarios testable
- [ ] Create traceability matrix
- [ ] Self-review complete

---

## Summary

**Spec production is about clarity and implementability.**

**Key principles**:
1. Use SHALL/MUST for normative requirements
2. Be specific, not vague
3. Every requirement needs testable scenarios
4. Include constraints and dependencies
5. Reference specification sections
6. Create design.md only when needed

**A good spec is one that the implementation team can build from without asking questions.**

---

**Next**: See [04-SPEC-VALIDATION.md](./04-SPEC-VALIDATION.md) for spec validation techniques.
