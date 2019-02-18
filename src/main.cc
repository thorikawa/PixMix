#include "dr.hh"
#include "tracking.hh"
#include "cmdline.h"
#include <string>

std::vector<cv::Point> cont;
unsigned int k = 0;
cv::Mat img, debug;

void mouseEvent(int evt, int x, int y, int flags, void *param)
{
    if (evt == CV_EVENT_LBUTTONDOWN)
	{
		cont.push_back(cv::Point(x, y));
		cv::circle(debug, cont[k], 10, cv::Scalar(0, 0, 155), -1);
		if (cont.size() > 1)
			cv::line(debug, cont[k - 1], cont[k], cv::Scalar(0, 0, 255));
		++k;
		cv::imshow("Mask building", debug);
    }
}


int main(int argc, char* argv[])
{
	cmdline::parser p;
	p.add<std::string>("input", 'i', "input image path", true);
	p.add<std::string>("mask", 'm', "mask image path", false, "");
	p.add<std::string>("output", 'o', "output image path", true);
	p.parse_check(argc, argv);

	std::list<std::pair<char*, char*> > tests;
	bool manual = p.get<std::string>("mask") == "";
	cv::Mat m;
	if (manual)
	{
		img = cv::imread(p.get<std::string>("input"));
		img.copyTo(debug);
		// cv::imshow("Mask building", debug);
		cvSetMouseCallback("Mask building", mouseEvent, 0);

		cv::waitKey(0);

		Tracking tr(cont);
		tr.build_mask(img);
		auto mask = tr.get_mask();
		// DR dr = DR(mask, img, prefix/*, DR::INTENSITY*/);
		DR dr = DR(mask, img, DR::INTENSITY);
		m = dr.inpaint();
	}
	else
	{
		auto mask = p.get<std::string>("mask");
		auto img = p.get<std::string>("input");
		DR dr(mask, img, DR::INTENSITY);
		m = dr.inpaint();
	}
	cont.clear();

	cv::imwrite(p.get<std::string>("output"), m);

	// cv::destroyAllWindows();

	return 0;
}
