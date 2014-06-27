# coding=utf-8

DEFAULT_KEY = "\x59\xf3\x02\xc3\x25\x9a\x82\x30\x0b\xbb\x25\x7f\x7e\x3b\xd2\xdc"

def rc4(data, key=DEFAULT_KEY, skip=1024):
    x = 0
    box = range(256)
    
	

    x = 0
    for i in range(256):
        x = (x + box[i] + ord(key[i % len(key)])) % 256
        tmp = box[i]
        tmp2 = box[x]
        box[i] = box[x]
        box[x] = tmp
    

    x = 0
    y = 0
    out = []
    if skip > 0:
        for i in range(skip):
            x = (x + 1) % 256
            y = (y + box[x]) % 256
            box[x], box[y] = box[y], box[x]
	
    for char in data:
        x = (x + 1) % 256
        y = (y + box[x]) % 256
        box[x], box[y] = box[y], box[x]
        k = box[(box[x] + box[y]) % 256]
        print k
        out.append(chr(ord(char) ^ k))

    return ''.join(out)

if __name__ == '__main__':
    # handle input file or stream
    import sys
    
    rc4("梯子网@91waijiao", "12345678", 0)


