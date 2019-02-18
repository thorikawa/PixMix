#include "dr.hh"
#include "tracking.hh"

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
	bool manual = false;
	std::string prefix("/path/to/images/");

	std::list<std::pair<char*, char*> > tests;
	tests.push_back(std::make_pair(strdup("mask.png"), strdup("input.png")));
	//tests.push_back(std::make_pair(strdup("2mask.png"), strdup("2.png")));



	std::list<std::pair<char*, char*> >::iterator it = tests.begin();
	for (; it != tests.end(); ++it)
	{
		// 2D inpainting, with a binary mask.

		if (manual)
		{
			img = cv::imread(prefix + it->second);
			img.copyTo(debug);
			cv::imshow("Mask building", debug);
			cvSetMouseCallback("Mask building", mouseEvent, 0);

			cv::waitKey(0);

			Tracking tr(cont);
			tr.build_mask(img);
			auto mask = tr.get_mask();
			// DR dr = DR(mask, img, prefix/*, DR::INTENSITY*/);
			DR dr = DR(mask, img, prefix, DR::INTENSITY);
			dr.inpaint();
		}
		else
		{
			// DR dr(it->first, it->second, prefix/*, DR::INTENSITY*/);
			DR dr(it->first, it->second, prefix, DR::INTENSITY);
			dr.inpaint();
		}
		cv::waitKey(0);
		cont.clear();
		cv::destroyAllWindows();
	}

  return 0;
}
