# DSA - Digital Signature Algorithm

Chương trình mô phỏng thuật toán chữ ký số DSA.

##  Cách chạy chương trình

### Windows

**Cách 1: Sử dụng batch files (Đơn giản nhất)**

```bash
# Build chương trình
.\build.bat

# Chạy chương trình
.\dsa_program.exe

# Hoặc build và chạy luôn
.\run.bat

# Xóa file build
.\clean.bat
```

**Cách 2: Compile thủ công**

```bash
gcc main.c prime.c generator.c dsa.c -o dsa_program.exe -lgmp
.\dsa_program.exe
```

### Linux/macOS

```bash
# Build và chạy
make run

# Hoặc
make
./dsa_program
```

## Test Vector 

Kết quả chạy chương trình với p bắt đầu từ 2^511:

```
Nhap do dai cua so nguyen to p (vi du: 512 hoac 1024): 512

Simulation of Digital Signature Algorithm

Global public key components are:

P is: 0x8000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000006f

Q is: 0x3bc8a3488306e1ed623b4b9516f4d8cd07ca2c508c7c9753a186e860e8d9feb8b5161686add222eab861b74ad28f1989daae6506e3e98ba733eed1753a9

G is: 0x7de14fd2a72100c68d389c3ec49b4b6d719a41b5f43248b1a1ab4b7fe107c3c572da40f1134ee26aea61284b666713d0fd97a9289c048eb78a5f1f89ab120806

Secret information:
X (private) is: 0x2f768b2e95073ccf70e101acd7cfaafbffebf1b28d71bfafc3d7203ab67682af3d52b7777d0a03c2efca3c56ebfb99599267c70248fd5b0e8bc74fad136
Y (public) is: 0x6c5a5f6660597ace6ab1235417cd89f089efce8796ba6d262ae453bffb9087188c314127229bb144278f9ee80f96dcddd36e64e261a4a2f8565760a248f6a907
H (mdhash) is: 0x80adb7eab3eff63f058ba30e848da545fe9d4d17c04830e556dd3eae063aeda16a2cd4c1d3a4fbe0033ec735fbc3d9043a6ce9f6b5f78f31251dc9be07f54375

Generating digital signature:
DSA Signature Generated:
R is: 0x21525afc22036fbaa849b210b461ac13f1aacb558397d9f2c8b2dad5306021be6ba506f0cf95f43b38e4a277513d7e7236ea96fef53bfd8362352055fd4
S is: 0x13b04924c68666d313469e6f6ab30550908fd006b514dbe9579439280b9c372f7eb2afcce962fe0344118c2661c7a1824a0c57c30ba71ee22f33d23312e

Verifying digital signature:
DSA Signature Verification Result: Valid

Success: Digital signature is verified!
0x21525afc22036fbaa849b210b461ac13f1aacb558397d9f2c8b2dad5306021be6ba506f0cf95f43b38e4a277513d7e7236ea96fef53bfd8362352055fd4
```
Kết quả của chương trình với p bắt đầu từ 2^999:

```
Nhap do dai cua so nguyen to p (vi du: 512 hoac 1024): 1000

Simulation of Digital Signature Algorithm

Global public key components are:

P is: 0x80000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000004d7

Q is: 0x56bdc9600a7190d80e9d668a460b66172b49338d1232782145e2b351cc98102892ae20a4218aa7f55d788c23468173f67c3f1f666eab0736951a193d1c8fe9865127c8cf5bd78a85ecbef992a778aaa2dc8a85515df02e08e8347713e11ea683e19d65f8ba91b1c32d6ae39999746101c1e82db97c5d

G is: 0x6951c5e2c7c41908612b7895f9b427b9463aaad07662bd7dccebca467152e842889591902ae0e2c2e50ef00d0c26cd5e5bbc32d3d8675cc8523aab6794a3e74622870de1340c2f25eb3a55647f114a6a3b9bec67d45c9cef1ba7a49f76028a4ee5cd46096262a45b65b050376b42a7f5e857cfdb05a2f256d65e078f7b

Secret information:
X (private) is: 0x1d7a4fb95088c08a4a6a06184fe4845f457e7568975693f18c71e44b5e3f8b4bbaeea4e155f5b2f048c3ad693f991d36cd643120fcc8a9d2364fc8d6e9c58b3347b3c9386e54e49a0af680d45339a896445e0f85a36572b61f67747f241d1f5ec3b4fa06efba32effbeb2e029de59128a975d7e6c3d
Y (public) is: 0x640ffe1ee84d111fc3411b26176863889685a8cafbf6022d038dc9c95c14e5f89d9cfc0102357b0d2a2510046eed3eee5cbb586bbfa621f41b34be6adafa48db10902c6737d5e60166ac900432407a1734f5b719992051b1895a05acc91dabe47e940f03680a23926169ea665018c366d7af70aeac8c1f4592ffc62eb4
H (mdhash) is: 0x8476d75b3e19f54a7a87e57e026599b6854a3be96b1115b5784e3266ce1f3c08608dc554582c1fd0558d8461b297b5f7c7e906263cb65da0357f4c62210554d759c4f677fe88f5d708bf694b038d9d547234b26572b51734b36874554e473d5d814d740af54de266badd6f9bf73e3422387dffd7705f47e8df4028d10c

Generating digital signature:
DSA Signature Generated:
R is: 0x527ac91eeac385debdf99df14f9327f7b6bb95f219fb5bf051afeacf06517503a4da34adee342d6f72e337dd3d0670d14bf69d71411a4ebb7cbc05ae1fb3c7ca7a7b3769bb6b2705b3884352356f4d38af7e50aceaf77f64f79e3476c56064f94ef6caa37959bbbdb743e83d70c597e2c7df782e6764
S is: 0x2f5bac52d86f0f705c188d13a3d1ea73f255ff048112115f7b042da2830196a8e6d59a57085c67d53da6d182106237a61dbb6675a9d080b1d8a18637f11b57985cb9edab9d2a50a7b95dcf4fdcb09b37c752c3bcf5f58f3884529b2571e3857ef041596e320722107d65bc4ab5757da881901c6cf9a7

Verifying digital signature:
DSA Signature Verification Result: Valid

Success: Digital signature is verified!
0x527ac91eeac385debdf99df14f9327f7b6bb95f219fb5bf051afeacf06517503a4da34adee342d6f72e337dd3d0670d14bf69d71411a4ebb7cbc05ae1fb3c7ca7a7b3769bb6b2705b3884352356f4d38af7e50aceaf77f64f79e3476c56064f94ef6caa37959bbbdb743e83d70c597e2c7df782e6764
```

**Giải thích:**
- **P**: Số nguyên tố L-bit được sinh từ 2^(L-1)
- **Q**: Ước số nguyên tố lớn nhất của (P-1)
- **G**: Generator của nhóm
- **X**: Khóa riêng (private key)
- **Y**: Khóa công khai (public key) = G^X mod P
- **H**: Hash của message (giả lập)
- **R, S**: Chữ ký số (signature)
- **Verification**: So sánh V với R để xác thực
