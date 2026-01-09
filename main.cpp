#include <SFML/Graphics.hpp>
#include <ctime>
#include <cmath>
#include <iostream>
#include<random>

const float PI = 3.14159265358979323846f;
const int WINDOW_WIDTH = 1085;
const int WINDOW_HEIGHT = 620;
const int BanKinhNhoNhat = 100;

float degToRad(float degrees) {
    return degrees * PI / 180.0f;
}

// Hàm tạo màu ngẫu nhiên
sf::Color getRandomColor() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<> dis(100, 255); // Giới hạn màu nhạt
    return sf::Color(dis(gen), dis(gen), dis(gen));
}

int main() {
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "UFO Landing", sf::Style::Default, settings);
    window.setFramerateLimit(60);


 // Background animation
    std::vector<sf::Texture> backgroundFrames;
    for (int i = 1; i <= 5; ++i) {
        sf::Texture frameTexture;
        if (!frameTexture.loadFromFile("mHoden" + std::to_string(i) + ".jpg")) {
            std::cerr << "Failed to load mHoden" << i << ".jpg" << std::endl;
            return -1;
        }
        backgroundFrames.push_back(frameTexture);
    }

    sf::Sprite backgroundSprite(backgroundFrames[0]);
    int currentFrame = 0;
    float frameTime = 6.1f;
    float frameTimer = 3.0f;
    sf::Texture DiaBayTexture;
    sf::Texture gradientRedTexture;
    sf::Texture gradientGrayBlueTexture;
    sf::Texture gradientBrownTexture;

    if (!gradientRedTexture.loadFromFile("gradient_tronDo.bmp")) {
    std::cerr << "Failed to load gradient.bmp!" << std::endl;
    return -1;
    }
    if (!gradientBrownTexture.loadFromFile("gradient_tronNau.bmp")) {
    std::cerr << "Failed to load gradient_tronNau.bmp!" << std::endl;
    return -1;
    }
    if (!gradientGrayBlueTexture.loadFromFile("gradient_tronXam.png")) {
    std::cerr << "Failed to load gradient.png!" << std::endl;
    return -1;
    }

    if (!DiaBayTexture.loadFromFile("UFO.png")) {
        std::cerr << "Failed to load UFO image!" << std::endl;
        return -1;
    }
    sf::Sprite DiaBaySprite(DiaBayTexture);

    sf::Texture UFOBaiDapTexture;
    if (!UFOBaiDapTexture.loadFromFile("UFOBaiDap.png")) {
        std::cerr << "Failed to load UFOBaiDap image!" << std::endl;
        return -1;
    }
    sf::Sprite UFOBaiDapSprite(UFOBaiDapTexture);

    // Tải hình ảnh nhân vật
    sf::Texture TauVuTru_Texture;
    if (!TauVuTru_Texture.loadFromFile("TauVT.png")) {
        std::cerr << "Failed to load TauVuTru image!" << std::endl;
        return -1;
    }
    sf::Sprite TauVuTruSprite(TauVuTru_Texture);

    sf::Texture VeTinh_Texture;
    if (!VeTinh_Texture.loadFromFile("VeTinh.png")) {
        std::cerr << "Failed to load VeTinh image!" << std::endl;
        return -1;
    }
    sf::Sprite VeTinhSprite(VeTinh_Texture);


    float DiaBayScale = 0.3f/2.5;
    float DiaBayX = WINDOW_WIDTH * 0.85f;
    float DiaBayY = -DiaBaySprite.getGlobalBounds().height;
    float DiaBaySpeed = 2.0f;
    float bounceAmplitude = 10.0f;
    float bounceFrequency = 0.1f;
    float bounceTime = 0.0f;

    float BaiDapScale = 0.5f/2;
    float BaiDapX = WINDOW_WIDTH * 0.85f;
    float BaiDapY = WINDOW_HEIGHT * 0.85f;
    float rotationAngle = 0.0f;
    float rotationSpeed = 1.0f;

    DiaBaySprite.setScale(DiaBayScale, DiaBayScale);
    UFOBaiDapSprite.setScale(BaiDapScale, BaiDapScale);
    UFOBaiDapSprite.setPosition(BaiDapX, BaiDapY);
    UFOBaiDapSprite.setOrigin(UFOBaiDapSprite.getLocalBounds().width / 2,
                             UFOBaiDapSprite.getLocalBounds().height / 2);
    DiaBaySprite.setOrigin(DiaBaySprite.getLocalBounds().width / 2,
                          DiaBaySprite.getLocalBounds().height / 2);

    int state = 0;  // 0: hạ cánh, 1: nảy, 2: đứng im, 3: ẩn, 4: hiện lại, 5: nảy lại, 6: bay lên
    bool keyPressed = false;

    // Hình tròn tĩnh viền ngoài
    sf::CircleShape outerStaticRedCircle(BanKinhNhoNhat + 50); // Bán kính lớn hơn đồng hồ
    outerStaticRedCircle.setFillColor(sf::Color::Transparent);
    outerStaticRedCircle.setOutlineThickness(1);
    outerStaticRedCircle.setOutlineColor(sf::Color(176,224,230));
    outerStaticRedCircle.setPosition(WINDOW_WIDTH / 2 - (BanKinhNhoNhat + 50), WINDOW_HEIGHT / 2 - (BanKinhNhoNhat + 50));

    sf::CircleShape outerStaticGrayBlueCircle(BanKinhNhoNhat + 90);
    outerStaticGrayBlueCircle.setFillColor(sf::Color::Transparent);
    outerStaticGrayBlueCircle.setOutlineThickness(1);
    outerStaticGrayBlueCircle.setOutlineColor(sf::Color(255,250,205));
    outerStaticGrayBlueCircle.setPosition(WINDOW_WIDTH / 2 - (BanKinhNhoNhat + 90), WINDOW_HEIGHT / 2 - (BanKinhNhoNhat + 90));

    sf::CircleShape outerStaticBrownCircle(BanKinhNhoNhat + 130);
    outerStaticBrownCircle.setFillColor(sf::Color::Transparent);
    outerStaticBrownCircle.setOutlineThickness(1);
    outerStaticBrownCircle.setOutlineColor(sf::Color(255,250,205));
    outerStaticBrownCircle.setPosition(WINDOW_WIDTH / 2 - (BanKinhNhoNhat + 130), WINDOW_HEIGHT / 2 - (BanKinhNhoNhat + 130));

    // Hình tròn xoay với gradient
    sf::CircleShape rotatingRedCircle(20);
    rotatingRedCircle.setTexture(&gradientRedTexture); // Áp dụng gradient
    rotatingRedCircle.setPosition(WINDOW_WIDTH / 2 - 20, WINDOW_HEIGHT / 2 - (BanKinhNhoNhat + 50 + 20));

    sf::CircleShape rotatingGrayBlueCircle(20);
    rotatingGrayBlueCircle.setTexture(&gradientGrayBlueTexture); // Áp dụng gradient
    rotatingGrayBlueCircle.setPosition(WINDOW_WIDTH / 2 - 20, WINDOW_HEIGHT / 2 - (BanKinhNhoNhat + 90 + 20));

    sf::CircleShape rotatingBrownCircle(20);
    rotatingBrownCircle.setTexture(&gradientBrownTexture); // Áp dụng gradient
    rotatingBrownCircle.setPosition(WINDOW_WIDTH / 2 - 20, WINDOW_HEIGHT / 2 - (BanKinhNhoNhat + 130 + 20));

    // Biến để điều khiển chuyển động
    float rotatingAngle = 0.0f;
    float rotatingSpeed = 1.0f; // Tốc độ xoay

    // Biến để vẽ xoắn ốc
    float spiralAngle = 0.0f;
    float spiralRadius = 0.0f;
    const float spiralMaxRadius = 100.0f; // Giới hạn bán kính xoắn ốc
    const float spiralThickness = 2.0f;

    // Biến để điều khiển nhân vật tàu vũ trụ
    float TauVuTruScale = 0.5f / 3; // Kích thước ban đầu
    float TauVuTruX = WINDOW_WIDTH; // Vị trí ban đầu (bên phải màn hình)
    float TauVuTruY = 10.0f;      // Vị trí ban đầu (phía trên màn hình)
    float TauVuTruSpeed = 1.0f;     // Tốc độ di chuyển
    float TauVuTruXSpeed = -1.0f;   // Tốc độ di chuyển theo trục x (từ phải sang trái)

    // Phần khai báo biến điều khiển nhân vật Vệ tinh
    float x = 100.0f;       // Giới hạn trái (x)
    float y = 100.0f;       // Giới hạn trên (y)
   float x1 = 300.0f;      // Giới hạn phải (x1)
   float y1 = 500.0f;      // Giới hạn dưới (y1)
   float VeTinhX = 100.0f; // Vị trí ban đầu của nhân vật (trục x)
   float VeTinhY = 200.0f; // Vị trí ban đầu của nhân vật (trục y)
   float VeTinhSpeed = 1.0f; // Tốc độ di chuyển theo trục y
   float VeTinhXSpeed = -0.5f; // Tốc độ di chuyển theo trục x
   float VeTinhScale = 1.0f/5; // Kích thước ban đầu của nhân vật


    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed && !keyPressed) {
                if (event.key.code == sf::Keyboard::Space) {
                    if (state == 1) state = 2;
                    else if (state == 2) state = 3;
                    else if (state == 3) state = 4;
                    else if (state == 4) state = 5;
                    else if (state == 5) state = 6;
                    else if (state == 6) state = 0;
                    keyPressed = true;
                }
            }
            if (event.type == sf::Event::KeyReleased) {
                keyPressed = false;
            }
        }

       frameTimer += 1.0f / 60.0f;
        if (frameTimer >= frameTime) {
            frameTimer = 0.0f;
            currentFrame = (currentFrame + 1) % backgroundFrames.size();
            backgroundSprite.setTexture(backgroundFrames[currentFrame]);
        }
        rotationAngle += rotationSpeed;
        if (rotationAngle >= 360.0f) rotationAngle -= 360.0f;

        float scaleY = fabs(cos(degToRad(rotationAngle)));
        UFOBaiDapSprite.setScale(BaiDapScale, BaiDapScale * scaleY);

        float landingCenterX = BaiDapX;
        float landingSurfaceY = BaiDapY - (UFOBaiDapSprite.getGlobalBounds().height / 2) * scaleY;
        float baseY = landingSurfaceY - (DiaBaySprite.getGlobalBounds().height / 2);

        switch (state) {
            case 0: // Hạ cánh
                DiaBayY += DiaBaySpeed;
                if (DiaBayY >= baseY) {
                    DiaBayY = baseY;
                    DiaBayX = landingCenterX;
                    state = 1;
                }
                break;
            case 1: // Nảy khi hạ cánh
                bounceTime += 0.1f;
                DiaBayY = baseY - bounceAmplitude * sin(bounceFrequency * bounceTime) * exp(-bounceTime * 0.5f);
                DiaBayX = landingCenterX;
                if (bounceTime > 10.0f) bounceTime = 10.0f;
                break;
            case 2: // Đứng im trên bãi đáp
                DiaBayY = baseY;
                DiaBayX = landingCenterX;
                break;
            case 3: // Ẩn cả hai
                break;
            case 4: // Hiện lại
                DiaBayX = landingCenterX;
                DiaBayY = baseY;
                bounceTime = 0.0f;
                state = 5;
                break;
            case 5: // Nảy lại khi hiện
                bounceTime += 0.1f;
                DiaBayY = baseY - bounceAmplitude * sin(bounceFrequency * bounceTime) * exp(-bounceTime * 0.5f);
                DiaBayX = landingCenterX;
                if (bounceTime > 10.0f) bounceTime = 10.0f;
                break;
            case 6: // Bay lên hẳn về vị trí ban đầu
                DiaBayY -= DiaBaySpeed;
                DiaBayX = landingCenterX;
                if (DiaBayY < -DiaBaySprite.getGlobalBounds().height) {
                    DiaBayY = -DiaBaySprite.getGlobalBounds().height;
                    DiaBayX = landingCenterX;
                    state = 0;
                }
                break;
        }

        DiaBaySprite.setPosition(DiaBayX, DiaBayY);

        window.clear();
        window.draw(backgroundSprite);

        if (state != 3) {
            window.draw(UFOBaiDapSprite);
            window.draw(DiaBaySprite);
        }

// Cập nhật vị trí và kích thước nhân vật
        //VeTinhY += VeTinhSpeed; // Di chuyển xuống dưới
        TauVuTruX += TauVuTruXSpeed; // Di chuyển từ phải sang trái
        TauVuTruScale == 0.001f; // +=Tăng kích thước dần
        TauVuTruSprite.setScale(TauVuTruScale, TauVuTruScale);
        TauVuTruSprite.setPosition(TauVuTruX, TauVuTruY);

        // Kiểm tra nếu tàu vũ trụ đi ra khỏi màn hình bên trái
        if (TauVuTruX + TauVuTruSprite.getGlobalBounds().width < 0) {
            TauVuTruX = WINDOW_WIDTH; // Đặt lại vị trí ban đầu (bên phải màn hình)
        }
        window.draw(TauVuTruSprite);

        // Cập nhật vị trí và kích thước nhân vật
    VeTinhX += VeTinhXSpeed; // Di chuyển theo trục x
    VeTinhY += VeTinhSpeed; // Di chuyển theo trục y
    VeTinhScale == 0.001f; // +=Tăng kích thước dần
    VeTinhSprite.setScale(VeTinhScale, VeTinhScale);
    VeTinhSprite.setPosition(VeTinhX, VeTinhY);

    // Kiểm tra và điều chỉnh vị trí Vệ tinh để không vượt quá giới hạn
    if (VeTinhX < x) {
        VeTinhX = x;
        VeTinhXSpeed = -VeTinhXSpeed; // Đổi hướng di chuyển theo trục x
    }
    if (VeTinhX + VeTinhSprite.getGlobalBounds().width > x1) {
        VeTinhX = x1 - VeTinhSprite.getGlobalBounds().width;
        VeTinhXSpeed = -VeTinhXSpeed; // Đổi hướng di chuyển theo trục x
    }
    if (VeTinhY < y) {
        VeTinhY = y;
        VeTinhSpeed = -VeTinhSpeed; // Đổi hướng di chuyển theo trục y
    }
    if (VeTinhY + VeTinhSprite.getGlobalBounds().height > y1) {
        VeTinhY = y1 - VeTinhSprite.getGlobalBounds().height;
        VeTinhSpeed = -VeTinhSpeed; // Đổi hướng di chuyển theo trục y
    }

    window.draw(VeTinhSprite);

        // Vẽ hình tròn tĩnh viền ngoài
        window.draw(outerStaticRedCircle);
        window.draw(outerStaticGrayBlueCircle);
        window.draw(outerStaticBrownCircle);

        // Cập nhật và vẽ hình tròn xoay
        rotatingAngle -= rotatingSpeed * 0.01f; // Đổi hướng quay ngược chiều kim đồng hồ
        if (rotatingAngle < -2 * PI) rotatingAngle += 2 * PI;

        float rotatingX = WINDOW_WIDTH / 2 + (BanKinhNhoNhat + 50) * cos(rotatingAngle);
        float rotatingY = WINDOW_HEIGHT / 2 + (BanKinhNhoNhat + 50) * sin(rotatingAngle);
        rotatingRedCircle.setPosition(rotatingX - 20, rotatingY - 20);

        float rotatingX1 = WINDOW_WIDTH / 2 + (BanKinhNhoNhat + 90) * cos(rotatingAngle + 90);
        float rotatingY1 = WINDOW_HEIGHT / 2 + (BanKinhNhoNhat + 90) * sin(rotatingAngle + 90);
        rotatingGrayBlueCircle.setPosition(rotatingX1 - 20, rotatingY1 - 20);

        float rotatingX2 = WINDOW_WIDTH / 2 + (BanKinhNhoNhat + 130) * cos(rotatingAngle + 130);
        float rotatingY2 = WINDOW_HEIGHT / 2 + (BanKinhNhoNhat + 130) * sin(rotatingAngle + 130);
        rotatingBrownCircle.setPosition(rotatingX2 - 20, rotatingY2 - 20); // Sửa vị trí hình tròn trắng

        window.draw(rotatingRedCircle);
        window.draw(rotatingGrayBlueCircle);
        window.draw(rotatingBrownCircle);

        // Vẽ xoắn ốc
        spiralAngle -= 0.05f; // Đổi hướng quay ngược chiều kim đồng hồ
        if (spiralRadius < spiralMaxRadius) {
            spiralRadius += 0.2f; // Tăng bán kính xoắn ốc
        }

        sf::VertexArray spiral(sf::LinesStrip);
        for (float r = 0; r < spiralRadius; r += 0.1f) {
            float theta = spiralAngle + r / 5.0f; // Góc xoắn ốc
            float x = WINDOW_WIDTH / 2 + r * cos(theta);
            float y = WINDOW_HEIGHT / 2 + r * sin(theta);
            spiral.append(sf::Vertex(sf::Vector2f(x, y), getRandomColor()));
        }
        window.draw(spiral);


        window.display();
    }

    return 0;
}
