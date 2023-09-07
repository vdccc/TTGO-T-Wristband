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

void Pages::drawCurrentPage(OSBase &osBase) {
  pages[currentPageIDX]->draw(osBase);
}

void Pages::runCurrentAction(OSBase &osBase) {
  pages[currentPageIDX]->run(osBase);
}

auto Pages::getCurrentRefreshInterval() -> int {
  return pages[currentPageIDX]->getRefreshInterval();
}

void Pages::nextPage() {
  for (; !pages[currentPageIDX]->available();) {
    currentPageIDX = ++currentPageIDX % pages.size();
  }
}

void Pages::pushPage(std::unique_ptr<Page> page) {
  pages.push_back(std::move(page));
}
