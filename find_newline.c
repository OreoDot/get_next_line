int find_newline (char *s)
{
    int i;

    if (!s)
        return(-1);

    i = 0;
    while (s[i] != '\0')
    {
        if(s[i] == '\n')
            return (i);
        i++;
    }
    return (-1);
}

char extract_line (char *stash)
{

}