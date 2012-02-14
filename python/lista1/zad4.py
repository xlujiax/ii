n = input('prosze podac liczbe')
print n

def cyfry(n):
   return map(int, str(n))

def suma_cyfr(n):
   return sum(cyfry(n))
   
def iloczyn_cyfr(n):
   return reduce(lambda acc, x: acc * x, cyfry(n), 1)

def fajna(n):
   return not 0 in cyfry(n) and n % iloczyn_cyfr(n) == 0 and n % suma_cyfr(n) == 0

one_to_n = range(1,n)

print filter(fajna, one_to_n)
