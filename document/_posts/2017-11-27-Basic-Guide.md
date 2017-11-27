---
layout: post
title:  "System Guide"
date:   2017-11-27 20:52:09 +0900
categories: guide
---
본 포스트는 교수자를 위한 시스템 가이드입니다.

<hr><br>
## 목차
1. 지원 언어
2. 개발 환경
3. 시스템 구성
4. 설치 및 환경 구축
5. API

<hr><br>

## 1. 지원 언어
- C
- C++ (GCC Compiler, POSIX API)

<br>

## 2. 개발 언어 및 환경
### 2-1. Framework
- Linux Ubuntu 14.04 LTS
- Python 3.5
- C++ ( C++11 or more)

### 2-2. Web Application Server
- MongoDB
- Express
- NodeJS

<br>

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

  {% highlight ruby %}
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
  {% endhighlight %}

- server  
  본 서버의 웹앱에 해당하는 부분입니다.  
  내부의 app.js를 실행하여 서버를 작동시킵니다.

<br>

## 4. 설치 및 환경 구축


<br>

## 5. API
