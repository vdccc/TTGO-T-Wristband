#include "os/pages.hpp"

#include <memory>

Pages::Pages() : curPageIDX(0) {
  pushPage(std::unique_ptr<Page>(new BasicDebug()));
  pushPage(std::unique_ptr<Page>(new WiFiControl()));
}

Pages::Pages(std::initializer_list<Page *> list) : curPageIDX(0) {
  for (Page *page : list) {
    pushPage(std::unique_ptr<Page>(page));
  }
}

void Pages::drawCurrentPage(OSBase &osBase) { pages[curPageIDX]->draw(osBase); }

void Pages::runCurrentAction(OSBase &osBase) { pages[curPageIDX]->run(osBase); }

auto Pages::getCurrentRefreshInterval() -> int {
  return pages[curPageIDX]->getRefreshInterval();
}

void Pages::nextPage() {
  curPageIDX = (curPageIDX + 1) % pages.size();
  // for (; !pages[curPageIDX]->available();) {
  //   curPageIDX = (curPageIDX + 1) % pages.size();
  // }
}

void Pages::pushPage(std::unique_ptr<Page> page) {
  pages.push_back(std::move(page));
}
