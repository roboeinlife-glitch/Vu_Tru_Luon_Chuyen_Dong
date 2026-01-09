# Vũ Trụ Luôn Chuyển Động

![C++](https://img.shields.io/badge/C++-17-blue.svg)
![SFML](https://img.shields.io/badge/SFML-2.5-green.svg)
![License](https://img.shields.io/badge/License-MIT-yellow.svg)
![Platform](https://img.shields.io/badge/Platform-Windows%20%7C%20Linux%20%7C%20macOS-lightgrey.svg)

Một mô phỏng đồ họa đơn giản về chuyển động của các vật thể trong vũ trụ, được viết bằng C++ với thư viện SDL2.

## Tính năng
- Hiển thị các hành tinh với kích thước và màu sắc ngẫu nhiên
- Chuyển động mượt mà với hiệu ứng vật lý cơ bản
- Xử lý va chạm đàn hồi giữa các hành tinh
- Màu nền
- gradient tạo cảm giác không gian vũ trụ

## Yêu cầu hệ thống
- Code::Blocks 20.03 trở lên
- Thư viện SDL2 (Simple DirectMedia Layer 2)

## Cài đặt và cấu hình trên Code::Blocks

### Bước 1: Cài đặt SDL2
1. Tải SDL2 Development Libraries từ trang chủ: https://libsdl.org/download-2.0.php
2. Chọn phiên bản phù hợp với hệ điều hành:
   - Windows: `SDL2-devel-2.x.x-mingw.tar.gz`
   - Linux: Cài qua package manager (ví dụ: `sudo apt-get install libsdl2-dev`)
   - macOS: `brew install sdl2`

### Bước 2: Cấu hình Code::Blocks (Windows)
1. Giải nén file SDL2 đã tải
2. Trong Code::Blocks:
   - **Settings → Compiler → Global compiler settings**
   - Tab **Search directories** → **Compiler**: Thêm đường dẫn đến thư mục `include` của SDL2
     - Ví dụ: `C:\SDL2\include`
   - Tab **Search directories** → **Linker**: Thêm đường dẫn đến thư mục `lib` của SDL2
     - Ví dụ: `C:\SDL2\lib\x64` (cho 64-bit) hoặc `C:\SDL2\lib\x86` (cho 32-bit)
   - Tab **Linker settings**: Thêm các thư viện sau:
     ```
     -lmingw32
     -lSDL2main
     -lSDL2
     ```

### Bước 3: Sao chép file DLL (Windows)
- Copy file `SDL2.dll` từ thư mục `lib\x64` hoặc `lib\x86` của SDL2 vào:
  - Thư mục project của bạn, HOẶC
  - Thư mục `bin` của Code::Blocks, HOẶC
  - Thư mục `C:\Windows\System32` (cho 64-bit) hoặc `C:\Windows\SysWOW64` (cho 32-bit)

### Bước 4: Tạo project mới trong Code::Blocks
1. **File → New → Project**
2. Chọn **Empty project**
3. Đặt tên project (ví dụ: "VuTruChuyenDong")
4. Thêm file `main.cpp` vào project
5. Copy nội dung từ GitHub vào file `main.cpp`

## Biên dịch và chạy

### Cách 1: Biên dịch trực tiếp
1. Mở project trong Code::Blocks
2. **Build → Build** (F9)
3. **Build → Run** (F10)

### Cách 2: Biên dịch thủ công (command line - Windows)
`bash
g++ main.cpp -o vutru.exe -I"C:\SDL2\include" -L"C:\SDL2\lib\x64" -lmingw32 -lSDL2main -lSDL2`

Chương trình được tạo bởi sự kết hợp giữa Grok AI (xAI) và DeepSeek AI

[Demo](https://www.youtube.com/watch?v=2sSo14tIaEw)

[Trở về trang chủ](https://github.com/roboeinlife-glitch)

