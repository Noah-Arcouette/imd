if (styleFlags & STRING)
{
  switch (data[i])
  {
    case '\'':
    case '"':
    case '`':
      styleFlags &= ~STRING;

      break;
    case '\n':
      styleFlags &= ~STRING | ~STYLE;

      break;
  }
}
else
{
  switch (data[i])
  {
    case ' ':
    case '\n':
    case '\t':
      styleFlags &= ~STYLE | ~STRING;

      sz += sizeof(SYNTAX_C);
      out = realloc(out, sz);
      strcat(out, SYNTAX_C);

      break;
    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
    case '.':
      sz += sizeof(NUMBER_C);
      out = realloc(out, sz);
      strcat(out, NUMBER_C);

      styleFlags |= STYLE;

      break;
    case '~':
    case '!':
    case '@':
    case '$':
    case '%':
    case '^':
    case '&':
    case '*':
    case '-':
    case '+':
    case '=':
    case '|':
    case ':':
    case ';':
    case ',':
    case '/':
    case '\\':
    case '<':
    case '>':
      sz += sizeof(OPERATOR_C);
      out = realloc(out, sz);
      strcat(out, OPERATOR_C);

      styleFlags |= STYLE;

      break;
    case '\'':
    case '"':
    case '`':
      sz += sizeof(STRING_C);
      out = realloc(out, sz);
      strcat(out, STRING_C);

      styleFlags |= STYLE | STRING;

      break;
    case '[':
    case ']':
    case '{':
    case '}':
    case '(':
    case ')':
      sz += sizeof(BRACKET_C);
      out = realloc(out, sz);
      strcat(out, BRACKET_C);

      styleFlags |= STYLE;

      break;
    default:
      sz += sizeof(SYNTAX_C);
      out = realloc(out, sz);
      strcat(out, SYNTAX_C);

      styleFlags &= ~STYLE | ~STRING;

      break;
  }
}
