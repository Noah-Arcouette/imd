switch (data[i])
{
  case ' ':
  case '\n':
  case '\t':
    flags &= ~STYLE;

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

    flags |= STYLE;

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
  case '/':
  case '\\':
  case '<':
  case '>':
    sz += sizeof(OPERATOR_C);
    out = realloc(out, sz);
    strcat(out, OPERATOR_C);

    flags |= STYLE;

    break;
  case '\'':
  case '"':
  case '`':
    sz += sizeof(STRING_C);
    out = realloc(out, sz);
    strcat(out, STRING_C);

    flags |= STYLE;

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

    flags |= STYLE;

    break;
  default:
    sz += sizeof(SYNTAX_C);
    out = realloc(out, sz);
    strcat(out, SYNTAX_C);

    flags &= ~STYLE;

    break;
}
