import cdan

def main():
    a = [1.2,3,0,-4]
    b = [-1.2,9,1.2,-8]

    l = cdan.loop_add(a,b)
    print("loop",l)

    s = cdan.simd_add(a,b)
    print("simd",s)

if __name__=='__main__':
    main()
