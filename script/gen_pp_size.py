import sys

head = '''
#ifndef CUB_MACRO_PP_SIZE_H__
#define CUB_MACRO_PP_SIZE_H__

#define __CUB_pp_empty()
#define __CUB_pp_concat(x, y) x ## y
#define __CUB_pp_paste(x, y) __CUB_pp_concat(x, y)

#ifdef _MSC_VER

#define __CUB_pp_size(...)  \\
   __CUB_pp_paste(__CUB_pp_size_i(__VA_ARGS__, \\
'''

middle = ''', __CUB_pp_empty())

#else

#define __CUB_pp_size(...)     \\
   __CUB_pp_size_i(__VA_ARGS__, \\
'''

end = '''

#endif

#define __CUB_pp_size_i( \\
'''

final = '''
   size
   
#define __CUB_pp_overload(prefix, ...)  __CUB_pp_paste(prefix, __CUB_pp_size(__VA_ARGS__))

#endif 
'''

def gen_seq(n):
    seq = ""
    m = 0
    for i in reversed(range(n)):
        seq = seq + "{}, ".format(i+1)
        m = m+1
        if m % 10 == 0:
            seq = seq + "\\\n      "

    return "      " + seq + ")"


def gen_var_seq(n):
    seq = ""
    m = 0
    for i in range(n):
        seq = seq + "e{}, ".format(i)
        m = m+1
        if m % 10 == 0:
            seq = seq + "\\\n      "

    return "      " + seq + "size, ...) \\"

def main():
    # print command line arguments
    if len(sys.argv) != 3:
        print("specify the num and file")
        exit(-1)

    n = int(sys.argv[1])
    lines = head
    lines = lines + gen_seq(n) + middle + gen_seq(n) + end + gen_var_seq(n) + final
    print(lines)

    file = open(sys.argv[2], "w")
    file.writelines(lines)
    file.close()

if __name__ == "__main__":
    main()