# DSA - Digital Signature Algorithm

Chương trình mô phỏng thuật toán chữ ký số DSA.

## 🚀 Cách sử dụng

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

**Sử dụng Makefile:**

```bash
# Build
make

# Chạy
make run

# Xóa file build
make clean

# Build lại từ đầu
make rebuild
```

**Compile thủ công:**

```bash
gcc main.c prime.c generator.c dsa.c -o dsa_program -lgmp
./dsa_program
```

## 📊 Output mẫu

```
Simulation of Digital Signature Algorithm

Global public key components are:

P is: 6703903964971298549787012499102923063739682910296196688861780721860882015036773488400937149083451713845015929093243025426876941405973284973216824503042159

Q is: 2986076933994148269835385919048238066318085404759171355727648743353559431103560755510084456357598398009587265648506906928241789019762235105800049577

G is: 6015047430874599381394216011476859772606675442184680414188038079540335120130511703792718258388735841588002188197780813289981908718711570593178812767494169

Secret information:
X (private) is: 2817030638416099911421757128812080249686178406136441769986574797139792355352939369610428542965311515413233542242392996736304229459417523344014413358
Y (public) is: 3004262697191857488544130731102282086358488836893110955392622610222229546087670703357236437544354661070894091644826251728698282311862453090524290751907408
H (mdhash) is: 3790618417092072329107766944971232787767480492405333836722068936774687252287317364427455702352886100145862638882709992329493177894401982003937944068045895

Generating digital signature:
DSA Signature Generated:
R is: 236996058167665009429628738106852837148506960921901302517472143250378119285012729000038462252536893478975041466532356736177291609389461523953561314
S is: 1017961334321594815661551610049652575835444508488105905015143672814765948086861422878977441005766535181359023500894395147443779341971064852422022536

Verifying digital signature:
DSA Signature Verification Result: Valid

Success: Digital signature is verified!
236996058167665009429628738106852837148506960921901302517472143250378119285012729000038462252536893478975041466532356736177291609389461523953561314
```

## 📚 Chi tiết kỹ thuật

### Các module chính

#### 1. **prime.c/h** - Xử lý số nguyên tố
- `isProbablePrime()`: Kiểm tra số nguyên tố bằng Miller-Rabin
- `getNextPrime()`: Tìm số nguyên tố tiếp theo
- `findQ()`: Tìm ước số nguyên tố lớn nhất

#### 2. **generator.c/h** - Sinh generator
- `getGen()`: Sinh generator g cho DSA

#### 3. **dsa.c/h** - Thuật toán DSA
- `DSA_sign()`: Ký số với khóa riêng
- `DSA_verify()`: Xác thực chữ ký với khóa công khai

#### 4. **main.c** - Chương trình chính
- Sinh các tham số DSA
- Demo ký và xác thực

### Quy trình DSA

**1. Sinh khóa:**
- Chọn p (số nguyên tố lớn, 512 bit)
- Tìm q (ước nguyên tố của p-1)
- Sinh generator g
- Chọn khóa riêng x ngẫu nhiên
- Tính khóa công khai y = g^x mod p

**2. Ký số:**
- Chọn k ngẫu nhiên
- Tính r = (g^k mod p) mod q
- Tính s = k^(-1) * (H + x*r) mod q
- Chữ ký: (r, s)

**3. Xác thực:**
- Tính w = s^(-1) mod q
- Tính u1 = H*w mod q
- Tính u2 = r*w mod q
- Tính v = (g^u1 * y^u2 mod p) mod q
- Xác thực: v == r

## 🔐 Bảo mật

**Lưu ý:**
- Đây là chương trình mô phỏng cho mục đích học tập
- Không sử dụng trong môi trường production
- Các số ngẫu nhiên cần nguồn entropy mạnh hơn
- Khóa 512-bit chỉ dùng cho demo (thực tế cần >= 2048-bit)

## 🐛 Xử lý lỗi

**Lỗi thường gặp:**

1. **"gmp.h: No such file or directory"**
   - Chưa cài thư viện GMP
   - Giải quyết: Cài GMP theo hướng dẫn phần Cài đặt

2. **"undefined reference to `__gmpz_init`"**
   - Chưa link thư viện GMP
   - Giải quyết: Thêm flag `-lgmp` khi compile

3. **"gcc: command not found"**
   - Chưa cài GCC
   - Giải quyết: Cài MinGW (Windows) hoặc build-essential (Linux)

## 👨‍💻 Tác giả

Dự án LTMM20251 - Lập trình Mật mã học

## 📄 License

MIT License - Tự do sử dụng cho mục đích học tập và nghiên cứu

## 🔗 Tham khảo

- [FIPS 186-4: Digital Signature Standard (DSS)](https://nvlpubs.nist.gov/nistpubs/FIPS/NIST.FIPS.186-4.pdf)
- [GMP Documentation](https://gmplib.org/manual/)
- [DSA Algorithm Explanation](https://en.wikipedia.org/wiki/Digital_Signature_Algorithm)

## 📝 Ghi chú phát triển

### TODO
- [ ] Tăng kích thước khóa lên 2048-bit
- [ ] Thêm đọc/ghi file cho khóa
- [ ] Implement SHA-256 cho hashing
- [ ] Thêm unit tests
- [ ] Tối ưu hiệu suất


