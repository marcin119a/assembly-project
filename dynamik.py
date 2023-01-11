import numpy as np 

def s(a,b):
  if a == '-' or b == '-':
    return 8
  if a == b:
    return 0 
  if (a == 'A' and b != 'G') or (a == 'C' and b != 'T') or (a == 'G' and b != 'A') or (a == 'T' and b != 'C'): 
    return 4
  else:
    return 2
    
import numpy as np 
r = np.zeros((5,5)) * 1
for x,sx in enumerate(['A', 'C', 'G', 'T', '-']):
  for y,sy in enumerate(['A', 'C', 'G', 'T', '-']):
    r[x][y] = s(sx,sy)
    
    
x = 'CTCGGCCCTAGG'
y = 'GGCTCTAGGCCC'


def overlap(x, y, min_l=4):
  D = np.zeros((len(x)+1, len(y)+1))

  for i in range(1,D.shape[1]):
    D[0][i] = np.Inf

  for i in range(1, D.shape[0]):
    for j in range(1, D.shape[1]):
      D[i][j] = min(D[i-1,j] + s(x[i-1], '-'), D[i,j-1] + s('-', y[j-1]), D[i-1,j-1]+ s(x[i-1], y[j-1])) 


  for j in range(D.shape[0]-min_l,D.shape[0]):
    D[j][0] = np.Inf
  for i in range(5):
    D[D.shape[1]-1][i] = np.Inf

  for i in range(D.shape[0]-min_l+1,D.shape[0]-1):
    for j in range(1,min_l+1):
      D[i][j] = min(D[i-1,j] + s(x[i-1], '-'), D[i,j-1] + s('-', y[j-1]), D[i-1,j-1]+ s(x[i-1], y[j-1])) 

  xf = ""
  yf = ""
  for i,j in zip(range(np.argmin(D[len(y),:]),0, -1), range(len(x)-1, 0, -1)):
    xf += f"{y[i-1]}"
    yf += f"{x[j]}"
    if y[i-1] == x[j]:
      score += 0

  return score, xf, yf
