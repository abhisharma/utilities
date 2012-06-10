# Computes the permutations of given word
def permutations(word):
    if len(word) <= 1:
        return [word]
    else:
        result = []
        perms = permutations(word[1:])
        for w in perms:
            for i in range(len(w)+1):
                newword = w[:i] + word[0] + w[i:]
                result += [newword]
        return result
print(permutations('word'))
