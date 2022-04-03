#include "CRecyclingSort.h"
#include "cvui.h"

#define FRAME_HEIGHT 300 // for video capture resolution
#define RECT_AREA_POSITIVE 10000

CRecyclingSort::CRecyclingSort() {
    // open video capture
    _video.open(-1, cv::CAP_ANY);

    // set camera resolution
    const cv::Size canvasSize = cv::Size(FRAME_HEIGHT*16/9, FRAME_HEIGHT);
    _video.set(cv::CAP_PROP_FRAME_WIDTH, canvasSize.width);
    _video.set(cv::CAP_PROP_FRAME_HEIGHT, canvasSize.height);

    // associate & init canvases
    _canvas = cv::Mat::zeros(canvasSize, CV_8UC3);
    cv::imshow("RGB", _canvas);
    _mask = cv::Mat::zeros(canvasSize, CV_8UC3);
    cv::imshow("MASK", _mask);
    _settings = cv::Mat::zeros(canvasSize, CV_8UC3);
    cv::imshow("SETTINGS", _settings);

    // init cvui
    cvui::init("SETTINGS");

    // set default servo pos
    gpioServo(pins::SERVO_MIDDLE, servoEnum::POS_MIDDLE);
    gpioServo(pins::SERVO_LEFT, servoEnum::POS_MIDDLE);
    gpioServo(pins::SERVO_RIGHT, servoEnum::POS_MIDDLE);
    // init io pins
    gpioSetMode(pins::LED_LEFT, PI_OUTPUT);
    gpioSetMode(pins::LED_MIDDLE, PI_OUTPUT);
    gpioSetMode(pins::LED_RIGHT, PI_OUTPUT);

    gpioSetMode(pins::BUTTON_LEFT, PI_INPUT);
    gpioSetPullUpDown(pins::BUTTON_LEFT, PI_PUD_UP);
    gpioSetMode(pins::BUTTON_MIDDLE, PI_INPUT);
    gpioSetPullUpDown(pins::BUTTON_MIDDLE, PI_PUD_UP);
    gpioSetMode(pins::BUTTON_RIGHT, PI_INPUT);
    gpioSetPullUpDown(pins::BUTTON_RIGHT, PI_PUD_UP);
	
	// Start Server Threads
	std::thread t1(&serverReceive); // receive commands from client
	t1.detach();
	std::thread t2(&serverSendIm); // send images repeatedly to client
	t2.detach();
	std::thread t3(&serverThread); // run the server thread
	t3.detach();
}

void CRecyclingSort::serverReceive() {
	std::vector<std::string> cmds;
	
	do {
		server.get_cmd(cmds);
		if (cmds.size() > 0) {
			//for (int i = 0; i < cmds.size(); i++) {
				//if (cmds.at(i) == CMDS::TOGGLE) {
					std::cout << cmds;
				//}
			//}
		}
	} while (!isExit());
}

void CRecyclingSort::serverSendIm() {
	if (video.isOpened()) {
		do {
			if (!_canvas.empty()) {
				// process message??
				server.set_txim(_canvas);
			}
		}
		while (!isExit());
	}
}

void CRecyclingSort::serverThread() {
	server.start(4618);
}

CRecyclingSort::~CRecyclingSort() {
server.stop();
//close video capture
_video.release();
cv::destroyAllWindows();
}

void CRecyclingSort::draw() {
    // put frame on canvas
    _video >> _canvas;
    if (_canvas.empty()) {
        std::cerr << "ERROR; blank frame\n";
    }

    // draw settings window
    ui_elements();
    int ball = segment_image();
    // show windows
    cv::imshow("RGB", _canvas);
    cv::imshow("MASK", _mask);
    cv::imshow("SETTINGS", _settings);

    // handles leds and buttons
    handleIO();

    // sort ball based on colour using servos
    if (enabled) { // automatic sorting
        sort_ball(ball);
    } else { // manual sorting
        sort_ball(manualsort);
    }
}

void CRecyclingSort::update() {
// not implemented atm
}

void CRecyclingSort::ui_elements() {
    _settings = cv::Mat::zeros(_settings.size(), CV_8UC3);
    cvui::text(_settings, 20, 20, "HSV Lower");
    cvui::trackbar(_settings, 0, 40, 200, &_bound_lower[0], (double) 0, (double) 179); // upper hue
    cvui::trackbar(_settings, 0, 85, 200, &_bound_lower[1], (double) 0, (double) 255);// upper saturation
    cvui::trackbar(_settings, 0, 130, 200, &_bound_lower[2], (double) 0, (double) 255);// upper value

    cvui::text(_settings, 270, 20, "HSV Upper");
    cvui::trackbar(_settings, 250, 40, 200, &_bound_upper[0], (double) 0, (double) 179);// lower hue
    cvui::trackbar(_settings, 250, 85, 200, &_bound_upper[1], (double) 0, (double) 255);// lower saturation
    cvui::trackbar(_settings, 250, 130, 200, &_bound_upper[2], (double) 0, (double) 255);// lower value

    cvui::text(_settings, 20, 200, "ERODE SIZE");
    cvui::trackbar(_settings, 0, 220, 200, &_erodeSize, (double) 1, (double) 10);// erosion size diameter
}

int CRecyclingSort::segment_image() {
    // segment into hsv
    cv::Mat hsv;
    cv::cvtColor(_canvas, hsv, cv::COLOR_BGR2HSV);
    cv::imshow("HSV", hsv);
    //cv::inRange(hsv, _bound_lower, _bound_upper, _mask);

    // check bounding rects
    //cv::contourArea(_mask);
    cv::inRange(hsv, _pink_ball_lower, _pink_ball_upper, _mask);
    cv::erode(_mask, _mask, cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(7,7)));
    cv::Rect pink_rect = cv::boundingRect(_mask);
    cv::rectangle(_canvas, pink_rect, RED);

    cv::inRange(hsv, _blue_ball_lower, _blue_ball_upper, _mask);
    cv::erode(_mask, _mask, cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(7,7)));
    cv::Rect blue_rect = cv::boundingRect(_mask);
    cv::rectangle(_canvas, blue_rect, BLUE);

    cv::inRange(hsv, _green_ball_lower, _green_ball_upper, _mask);
    cv::erode(_mask, _mask, cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(7,7)));
    cv::Rect green_rect = cv::boundingRect(_mask);
    cv::rectangle(_canvas, green_rect, cv::Scalar(0,255,0));

    cv::inRange(hsv, _yellow_ball_lower, _yellow_ball_upper, _mask);
    cv::erode(_mask, _mask, cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(_erodeSize,_erodeSize)));
    cv::Rect yellow_rect = cv::boundingRect(_mask);
    cv::rectangle(_canvas, yellow_rect, cv::Scalar(0,255,255));

    if (pink_rect.area() > RECT_AREA_POSITIVE) {
        //std::cout << "PINK BALL DETECTED" << std::endl;
        return ballType::PINK;
    } else if (blue_rect.area() > RECT_AREA_POSITIVE) {
        //std::cout << "BLUE BALL DETECTED" << std::endl;
        return ballType::BLUE;
    } else if (green_rect.area() > RECT_AREA_POSITIVE) {
        //std::cout << "GREEN BALL DETECTED" << std::endl;
        return ballType::GREEN;
    } else if (yellow_rect.area() > RECT_AREA_POSITIVE) {
        //std::cout << "YELLOW BALL DETECTED" << std::endl;
        return ballType::YELLOW;
    } else {
        //std::cout << "NOTHING DETECTED" << std::endl;
        return ballType::NOTHING;
    }
}

void CRecyclingSort::sort_ball(int _ball) {
    static auto start = std::chrono::_V2::system_clock::now();
    static auto ball = _ball;

    // if block for executing time-based servo movements
    if (std::chrono::_V2::system_clock::now() - start > std::chrono::milliseconds(servoEnum::WAIT_TIME*5/2)) {        // reset timer
        start = std::chrono::_V2::system_clock::now();
        ball = _ball;
        manualsort = -1; // tell system manual sort is completed
    } else if (std::chrono::_V2::system_clock::now() - start > std::chrono::milliseconds(servoEnum::WAIT_TIME*3/2)) { // reset servos to middle pos
        // set default servo pos
        gpioServo(pins::SERVO_MIDDLE, servoEnum::POS_MIDDLE);
        gpioServo(pins::SERVO_LEFT, servoEnum::POS_MIDDLE);
        gpioServo(pins::SERVO_RIGHT, servoEnum::POS_MIDDLE);
    } else if (std::chrono::_V2::system_clock::now() - start > std::chrono::milliseconds(servoEnum::WAIT_TIME)) {   // set left/right servo
        if (ball == ballType::PINK) {              // pink goes left, yellow goes right
                gpioServo(pins::SERVO_LEFT, servoEnum::POS_LEFT);
            } else if (ball == ballType::YELLOW) {
                gpioServo(pins::SERVO_LEFT, servoEnum::POS_RIGHT);
            } else if (ball == ballType::BLUE) {                                                                      // blue left, green right
                gpioServo(pins::SERVO_RIGHT, servoEnum::POS_LEFT);
            } else if (ball == ballType::GREEN) {
                gpioServo(pins::SERVO_RIGHT, servoEnum::POS_RIGHT);
            }
    } else {                                                                                                        // set middle servo
            // pink and yellow go left, blue and green go right
        if (ball == ballType::PINK || ball == ballType::YELLOW) {
            gpioServo(pins::SERVO_MIDDLE, servoEnum::POS_LEFT);
        } else if (ball == ballType::BLUE || ball == ballType::GREEN) {
            gpioServo(pins::SERVO_MIDDLE, servoEnum::POS_RIGHT);
        }
    }
}

void CRecyclingSort::handleIO() {
    // get pushbutton states
    char keypress = cv::waitKey(10);
    if (control.get_button(pins::BUTTON_LEFT) || keypress == '1') { // sort ball to left
        manualsort = ballType::GREEN;
    } else if (control.get_button(pins::BUTTON_RIGHT) || keypress == '2') { //sort ball to right
        manualsort = ballType::PINK;
    } else if (control.get_button(pins::BUTTON_MIDDLE) || keypress == 's') { // toggle system on/off
        enabled ^= 1;
        gpioWrite(pins::LED_MIDDLE, enabled);
    }
    // write LED states
    if (manualsort == ballType::GREEN) {
        gpioWrite(pins::LED_LEFT, PI_HIGH);
        gpioWrite(pins::LED_RIGHT, PI_LOW);
    } else if (manualsort == ballType::PINK) {
        gpioWrite(pins::LED_RIGHT, PI_HIGH);
        gpioWrite(pins::LED_LEFT, PI_LOW);
    }

    if (enabled) {
        gpioWrite(pins::LED_RIGHT, PI_LOW);
        gpioWrite(pins::LED_LEFT, PI_LOW);
    }
}