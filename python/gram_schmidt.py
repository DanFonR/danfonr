import numpy as np
def gs_ort(arr):	
	def proj(v1, v2):
		return np.dot(v1, v2)/np.dot(v2, v2)*v2
	res = [arr[0]]
	for i in range(1, len(arr)):
		temp = arr[i] - sum(proj(arr[i], res[j]) for j in range(len(res)))
		res.append(temp)
	return np.array(res)
A = np.array([[1, 2, 3], [-1, 3, 2], [1, 0, 0]])
B = gs_ort(A)
print(B)