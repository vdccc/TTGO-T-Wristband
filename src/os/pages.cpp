#include "os/pages.hpp"
#include <memory>

Pages::Pages() {
  pushPage(std::unique_ptr<Page>(new BasicDebug()));
  pushPage(std::unique_ptr<Page>(new WiFiControl()));
}

Pages::Pages(std::initializer_list<Page *> list) {
  for (Page *page : list) {
    pushPage(std::unique_ptr<Page>(page));
  }
}

void Pages::drawCurrentPage(OSBase &os) { pages[currentPageIDX]->draw(os); }

void Pages::runCurrentAction(OSBase &os) { pages[currentPageIDX]->run(os); }

int Pages::getCurrentRefreshInterval() {
  return pages[currentPageIDX]->getRefreshInterval();
}

void Pages::nextPage() {
  do {
    currentPageIDX = (currentPageIDX + 1) % pages.size();
  } while (!pages[currentPageIDX]->available());
}

void Pages::pushPage(std::unique_ptr<Page> page) {
  pages.push_back(std::move(page));
}
