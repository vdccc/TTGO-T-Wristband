#include "os/pages.hpp"

Pages::Pages() : curPageIDX(0) {
  pushPage(std::unique_ptr<Page>(new Clock()));
  pushPage(std::unique_ptr<Page>(new BasicDebug()));
  pushPage(std::unique_ptr<Page>(new WiFiControl()));
}

Pages::Pages(std::initializer_list<Page *> list) : curPageIDX(0) {
  for (Page *page : list) {
    pushPage(std::unique_ptr<Page>(page));
  }
}

void Pages::setupCurrentPage(OSBase &osBase) {
  pages[curPageIDX]->setup(osBase);
}

void Pages::teardownCurrentPage(OSBase &osBase) {
  pages[curPageIDX]->teardown(osBase);
}

void Pages::drawCurrentPage(OSBase &osBase) { pages[curPageIDX]->draw(osBase); }

void Pages::runCurrentActionHeld(OSBase &osBase) {
  pages[curPageIDX]->actionHeld(osBase);
}
void Pages::runCurrentActionDoubleClick(OSBase &osBase) {
  pages[curPageIDX]->actionDoubleClick(osBase);
}
void Pages::runCurrentActionTripleClick(OSBase &osBase) {
  pages[curPageIDX]->actionTripleClick(osBase);
}

auto Pages::getCurrentRefreshInterval() -> int {
  return pages[curPageIDX]->getRefreshInterval();
}

void Pages::nextPage(OSBase &osBase) {
  curPageIDX = (curPageIDX + 1) % pages.size();
  for (; !pages[curPageIDX]->available(osBase);) {
    curPageIDX = (curPageIDX + 1) % pages.size();
  }
}

void Pages::pushPage(std::unique_ptr<Page> page) {
  pages.push_back(std::move(page));
}
