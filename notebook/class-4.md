## Class 4

### Things not to use with sprintf

- attacker controlled format strings (use %s instead)
- buffer overflows (use snprintf instead)
- %n (don't use it)
- unstructured logs (sanitize your logs)