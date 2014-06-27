package com.langtaojin.cipher.impl;

import com.google.inject.Inject;
import com.google.inject.name.Named;
import com.langtaojin.cipher.CipherCrypt;

public class RC4 implements CipherCrypt {
    private final byte[] s = new byte[256];
    private int x,y;

    @Inject
    public RC4(@Named("RC4Key") byte[] key) {
        for(int i=0;i<256;i++)
            s[i] = (byte)i;
        for(int i=0,j=0;i<256;i++) {
            j = (j + (s[i]&0xff) + (key[i%key.length]&0xff))&0xff;
            byte tmp = s[i];
            s[i] = s[j];
            s[j] = tmp;
        }
    }

    @Override
    public int encrypt(byte[] in, int in_offset, byte[] out,
            int out_offset, int len) {
        int x = this.x;
        int y = this.y;
        byte[] s = this.s;
        for(int i=0;i<len;i++) {
            x = (x + 1) & 0xff;
            y = (y + (s[x]&0xff)) & 0xff;
            byte tmp = s[x];
            s[x] = s[y];
            s[y] = tmp;
            int t = ((s[x]&0xff) + (s[y]&0xff))&0xff;
            int k = s[t];
            out[out_offset+i] = (byte)((in[in_offset+i]&0xff)^k);
        }
        this.x = x;
        this.y = y;
        return 0;
    }

    @Override
    public int decrypt(byte[] in, int in_offset, byte[] out,
            int out_offset, int len) {
        return encrypt(in, in_offset, out, out_offset, len);
    }

    @Override
    public byte[] encrypt(byte[] in) {
        byte[] results = new byte[in.length];
        encrypt(in, 0, results, 0, in.length);
        return results;
    }

    @Override
    public byte[] decrypt(byte[] in) {
        byte[] results = new byte[in.length];
        decrypt(in, 0, results, 0, in.length);
        return results;
    }
}
