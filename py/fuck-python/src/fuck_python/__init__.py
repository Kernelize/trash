import ddddocr


def main() -> int:
    orc2 = ddddocr.DdddOcr(beta=True, show_ad=False)

    results = [
        orc2.classification(open(f"image{i}.jpeg", "rb").read())
        for i in range(1, 11)
    ]
    print(results)

    return 0

def myfunc(a: int) -> int:
    b = a + 2
    return b + 1
