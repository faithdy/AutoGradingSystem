<!-- 대문 -->
# Auto Grading System
Auto Grading System은 C/C++ 기반 학부 프로그래밍 과제를 자동으로 채점해주는 프로그램입니다.  
본 프로그램은 C++ 기반 오픈 소스 프레임 워크인 [Google Test](https://github.com/google/googletest)를 사용하였으며, MEAN 스택을 이용하여 웹 애플리케이션을 구현하였습니다.  

본 시스템은 연구 및 개발이 진행중인 프로젝트입니다.  

<!-- 목차 -->
# 목차
다음은 Auto Grading System에 대한 목차입니다.
1. [특징](#특징)
2. [사용법](#사용법)
3. [사용 환경](#사용-환경)

# 특징
Auto Grading System은 소프트웨어 교육, 그 중에도 **자료구조**와 **알고리즘** 학습에 도움이 되고자 하는 목적으로 시작하였습니다. 이에 따라 본 시스템은 다음 두가지의 핵심 원칙에 따라 개발되었습니다.

<!-- 부가적인 특징은 수정이 필요함 -->
 * **자동화를 통한 원가 절감** : 채점, 관리 및 피드백에 필요한 시간과 비용을 보다 효율적이고 객관적인 척도를 적용하기 위하여 자동화 시스템을 도입하였습니다.  
    - 웹 기반 UI
    - 모니터링
    - 실시간 처리  


 * **소스 코드 품질 검증** : 소스 코드 품질 검증을 위해 본 시스템은 CISQ(The Consortium for IT Software Quality)에서 정의한 [Code Quality Standards](http://it-cisq.org/standards/) 척도를 준수하였으며, 자료구조 및 알고리즘 검증을 위해 필요한 테스팅을 중점적으로 구현하였습니다. 다음은 핵심 테스팅 기법들입니다.  
    - Death Test를 통한 메모리 접근 오류 검증
    - Unit Test를 통한 함수별 채점
    - Mock Up & Dependency Injection를 통한 클래스 내 메소드 검증
    - Graph Isomorphism Problem 알고리즘 적용

# 사용법
## API, 환경 설정
다음은 교수자를 위한 보조 함수 및 API, 과제 환경 파일 작성법입니다.
### 1. API
본 시스템에서 제공하는 API 목록과 prototype입니다.
``` c++
1. 동형성 검사
bool isIsomorphic(Graph *G1, Graph *G2);
/*
  description : 자료구조 클래스의 동형성 관계를 검사하는 함수.
                제공되는 자료구조는 다음과 같다.
                - list
                - tree
                - graph   
  input : 자료구조 클래스 G
          G1은 테스트 할 클래스를, G2는 예측 상태의 클래스에 해당한다.
  output : 동형 관계라면 true, 그렇지 않다면 false를 리턴.
*/
```

``` c++
2. 콘솔 비교 검사
bool printedTest(String sentence, const int opt, callback);
/*
  description : 콘솔에 출력되는 결과를 검사하는 함수이다.
  input : 예상되는 문자열 sentence와 테스트할 함수의 포인터 callback,
          그리고 정규 표현식을 사용할지에 대한 여부인 opt로 구성.
          opt가 0이라면 정규 표현식을 사용하지 않으며, 기본 값으로 설정되어 있고,
          opt가 1이라면 정규 표현식을 사용한다.
  output : 출력 문자열이 문자열 sentence와 일치하면 true, 그렇지 않다면 false를 리턴.
*/
```

### 2. 환경 설정
본 시스템에서 사용하는 환경 파일 conf.cc에 대한 작성법입니다.
``` python
total_index = 2 // 테스트 suite의 총 갯수를 기입.

scenario_0 // 테스트 suite의 번호.
death_index = 0 1 // wrapper 사용 여부. 기재된 번호는 wrapping 되지 않음. 
function_0 = Graph G1, G2;
function_1 = G1.insert(30); G2.insert(30);
scenario_1 = isIsomorphic(G1,G2)
```


## 시연동영상
<!-- 그림 캡쳐 및 동영상으로 설명할 것 -->
[![시연 동영상](http://img.youtube.com/vi/KI-fHvDp0Wo/0.jpg)](https://www.youtube.com/embed/KI-fHvDp0Wo)

<!-- 혹은 필요하다면 다른 마크다운 문서로 링크를 걸것. (초보/고급) -->

# 사용 환경
본 시스템에서 이용한 환경 및 프레임 워크는 다음과 같습니다.  

* Web Application
    - MongoDB
    - Express
    - AngularJS
    - NodeJS  


* Middle Ware
    - GoogleTest
    - Linux 16.04 LTS
