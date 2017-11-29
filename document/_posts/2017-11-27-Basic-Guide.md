---
layout: post
title:  "System Guide"
date:   2017-11-27 20:52:09 +0900
categories: guide
---
<!-- 해야할 것.
- [ ] info 안에 setup.cc, 교수자 소스코드 설명
- [ ] 시스템 구동 부분 설명
- [ ] module 설명 및 API 설명
-->

본 포스트는 교수자를 위한 시스템 가이드입니다.  
시작하기에 앞서 프레임 워크 내에 어떤 모듈이 있는지를 알고 있다고 가정하고 진행합니다. 만일 모듈 정보와 API가 궁금하다면 [이전 글](/guide/2017/11/27/Framework-Module-And-API-Reference.html)을 참고해주세요.

<hr><br>
## 목차
1. 지원 언어
2. 개발 환경
3. 시스템 구성
4. 설치 및 환경 구축

<hr><br>

## 1. 지원 언어
- C
- C++ (GCC Compiler, POSIX API)

<hr><br>

## 2. 개발 언어 및 환경
### 2-1. Framework
- Linux Ubuntu 14.04 LTS
- Python 3.5
- C++ ( C++11 or more)

### 2-2. Web Application Server
- MongoDB
- Express
- NodeJS

<hr><br>

## 3. 시스템 구성
다음의 그림은 해당 시스템의 Root 시점에서의 디렉토리입니다.

<img src="/src/system_strcture_top.png" alt="System Structure(TOP)">

- AutoGradingSystem  
  본 시스템의 Framework가 위치해 있는 디렉토리입니다.  
  Python 스크립트와 Google Test, C++로 구성되어 있으며,  
  채점 시스템 전반에 걸친 모든 프로세스가 실행되는 공간입니다.  

- document  
  본 시스템의 github.io를 위한 디렉토리입니다.

- public  
  학습자의 과제를 저장하는 디렉토리입니다.

```
  public/
    - {project name}/
      - data/
        - {Student ID}/
          - Many Source & Header Files...
          ...
        ...

      - info/
        - {project name}.json /* Framework 통신 */

      - result/
        - {Student ID}/
          - Many Reporting Files...
          ...
        ...

    - {project name}/
      ...
```
public 내부 디렉토리 구조는 4-3. 사용법에서 자세히 다룹니다.
- server  
  본 서버의 웹앱에 해당하는 부분입니다.  
  내부의 app.js를 실행하여 서버를 작동시킵니다.

<hr><br>

## 4. 설치 및 환경 구축
### 4-1. 필요 조건
- Linux Ubuntu 14.04 LTS
- Python 3.5
- Google Test  

### 4-2 환경 구축
- 본 [저장소](https://github.com/faithdy/autogradingsystem)에는 Google Test가 빌트-인 되어있습니다.
- 본 시스템의 환경은 **Ubuntu 14.04 LTS**에서 구축되었으므로, Ubuntu 환경 하에서 저장소를 clone해주세요.
- 이후, sudo apt-get install 명령어를 이용하여 **python 3.5**, **nodeJS**를 설치합니다.
- 웹서버를 구동시킬 경우 server/ 디렉토리에서 npm install를 이용하여 필요한 패키지를 설치합니다. 설치가 다 되었다면 쉘 스크립트에 **nodemon**, 혹은 **npm start** 명령어를 입력하여 서버를 구동시킬 수 있습니다. (기본 포트는 3000번 입니다.)

### 4-3 사용법
#### 웹 서버를 통한 접근
- 웹 서버를 통한 접근은 다음 동영상을 참고해주세요.  
[웹 서버를 통한 채점 시스템 접근](https://www.youtube.com/embed/KI-fHvDp0Wo)

#### 프레임 워크에 직접 접근
1. root 디렉토리 밑에 **public** 디렉토리를 생성합니다.
2. public 디렉토리 밑에 해당하는 **과제 프로젝트의 이름**으로 디렉토리를 생성합니다.  
```
ex) public/DS_2017_project_1/
```
3. 해당하는 프로젝트 디렉토리 밑에 **data**, **info**, **result**라는 디렉토리를 생성합니다.  
```
ex) DS_2017_project_1/data  
       DS_2017_project_1/info  
       DS_2017_project_1/result  
```          
3-1. info 관련  
1) **프로젝트 이름과 동일한 json 파일**을 생성해줍니다.  
```
ex) info/DS_2017_project_1.json  
```
2) json 파일은 채점 간 **어떤 모듈을 사용할지에 대한 파일**입니다.  
사용하고자 하는 모듈은 true로, 아니라면 false를 입력해주세요.
```
json파일은 다음과 같이 구성됩니다.
    {
      "compile":true,
      "compatibility":true,
      "oop":false,
      "death":false,
      "unit":true
    }
```
3-2. data & result 관련  
data와 result 디렉토리는 각 학습자에 대한 **소스 코드** 및 **채점 레포팅**을 저장하는 디렉토리입니다.  
1) data 디렉토리에 해당하는 학생의 **학번**으로 디렉토리를 생성합니다.    
```
ex) data/2012722002/
```
2) 생성한 학번 디렉토리 밑에 학습자의 과제를 저장합니다.  
```
working directory is '/public/data/'
ex) 2012722002/BST.cc  
       2012722002/BST.h  
       2012722002/Manager.cc  
       ...  
```
3) 채점이 완료 되었다면 result 디렉토리 아래 대상이 되는 학번 디렉토리의 채점 결과 산출물이 저장 되어 있을 것입니다.
```
working directory is '/public/result/'
ex) 2012722002/DeathReport.xml
       2012722002/UnitReport.xml
       ...
```


#### 채점 프로세스 가동
1. root 디렉토리 밑에 **AutoGradingSystem** 디렉토리로 이동합니다.
2. 쉘 스크립트에 python main.py 명령어 입력 후 인자 값으로 과제 프로젝트 이름을 입력하면 public/프로젝트 이름/data/ 디렉토리 내의 학습자 폴더들을 탐색하여 채점 프로세스를 진행합니다.
```
ex) python main.py DS_2017_project_1
```
<!-- 3. 만일 특정 학습자만 채점하기를 원한다면 다음 인자 값을 추가로 명령합니다.
```
ex) python main.py DS_2017_project_1
``` -->
<br>
