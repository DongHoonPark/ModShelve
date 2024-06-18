#define CATCH_CONFIG_MAIN  // 이 매크로는 main() 함수를 정의합니다.

#include "catch2/catch_all.hpp"
#include "ModShelve.h"     // 테스트할 라이브러리의 헤더 파일

TEST_CASE("ModShelve functionality", "[ModShelve]") {
    ModShelve shelf;
    REQUIRE(shelf.mb_mem_block == nullptr);  // 예제 테스트 케이스
}