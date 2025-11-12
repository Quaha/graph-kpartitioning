from scipy.io import mmread

EPS = 1e-12

def is_symmetric_matrix(path):
    A = mmread(path).tocoo()

    if A.shape[0] != A.shape[1]:
        return False

    A_T = A.T.tocoo()
    if (A != A_T).nnz == 0:
        return True

    edges = {(int(i), int(j)): float(w) for i, j, w in zip(A.row, A.col, A.data)}
    for (u, v), w in edges.items():
        if (v, u) not in edges:
            return False
        if abs(edges[(v, u)] - w) > EPS:
            return False
    return True


def main():
    with open("mtx_names.txt", "r", encoding="utf-8") as f:
        names = [line.strip() for line in f if line.strip()]

    bad_matrices = []

    for name in names:
        try:
            if not name.lower().endswith(".mtx"):
                name += ".mtx"
            print(f"Checking {name} ...", end=" ")

            if is_symmetric_matrix(name):
                print("OK")
            else:
                print("Incorrect!")
                bad_matrices.append(name)

        except Exception as e:
            print(f"Error: ({e})")
            bad_matrices.append(name)

    print("\n========")
    if bad_matrices:
        print("Bad matrices:")
        for name in bad_matrices:
            print(" -", name)
    else:
        print("All matrices are correct")

    input("\n\nPress ENTER...")


if __name__ == "__main__":
    main()
