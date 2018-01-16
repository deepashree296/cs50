from nltk.tokenize import sent_tokenize


def lines(a, b):
    """Return lines in both a and b"""

    a = set(a.splitlines())
    b = set(b.splitlines())
    c = []
    for line in a:
        if line in b:
            c.append(line)
    return c


def sentences(a, b):
    """Return sentences in both a and b"""

    # implementing
    a = set(sent_tokenize(a))
    b = set(sent_tokenize(b))
    c = []
    for sent in a:
        if sent in b:
            c.append(sent)
    return c


def substrings(a, b, n):
    """Return substrings of length n in both a and b"""

    # implementing
    c = set()
    d = set()
    res = []
    for i in range(len(a) - n + 1):
        c.add(a[i:i + n])

    for i in range(len(b) - n + 1):
        d.add(b[i:i + n])

    c = set(c)
    d = set(d)

    for subs in c:
        if subs in d:
            res.append(subs)
    return res
