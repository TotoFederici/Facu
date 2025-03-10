def reverse(l: list) -> list:
    return l[::-1]

def palindromo(string: str) -> str:
    substring = []
    maslargo = []
    listString = [char for char in string if char != " "]
    
    largo = len(listString)
    for i in range(largo):
        for j in range(largo+i):
            substring = listString[i:j+1]
            if substring == reverse(substring) and len(substring) > len(maslargo):
                maslargo = substring
                
    result = "".join(maslargo)
    print(result)
    return result

palindromo("la paella lleva queso y papa")