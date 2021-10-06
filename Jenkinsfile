pipeline {
  agent any
  triggers {
    pollSCM('* * * * *')
    cron('30 23 * * *') 
  }
  stages {
    stage('cppcheck') {
      steps {
        sh 'cppcheck --xml --xml-version=2 ./src 2> cppcheck.xml'
      }
    }
    stage('build') {
      parallel {
        stage('build_linux') {
          steps {
            sh "docker build -t asneg/opcuapixtendserver${env.BUILD_ID} ."
          }
        }
      }
    }
  }

  post {
    cleanup {
        sh "docker image rm asneg/opcuapixtendserver${env.BUILD_ID}"
        deleteDir()
    }
  }
}
