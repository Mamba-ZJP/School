let alpha, beta, rho, Q, antNumber, maxIterations, antGroup, pheromone, cityNumber;
// 信息素因子, 启发函数因子, 信息挥发因子, 信息素常量, 蚂蚁数量, 最大迭代次数, 蚂蚁群, 信息素矩阵
const map = [];

function Ant(startCity) {
    this.path = [startCity];
    this.hasVisitedCity = [startCity];
    this.sumOfDistance = 0.0;

    this.Travel = function() {
        for (let i = 0; i < cityNumber - 1; i++) {
            let currentCity = this.path[this.path.length - 1];
            let sum = this.CalculateDown(currentCity);
            let nextCity = this.ChooseNextCity(currentCity, sum);
            this.Update(currentCity, nextCity);
        }
        this.GoBackStart();    
    };

    this.GoBackStart = function() {
        this.sumOfDistance += Distance(this.path[this.path.length - 1], this.path[0]);
        this.path.push(this.path[0]);
    }

    this.ChooseNextCity = function(currentCity, sum) {
        let city, maximalPossibility = 0.0;
        for (let nextCity = 0; nextCity < cityNumber; nextCity++) {
            if (this.hasVisitedCity.indexOf(nextCity) !== -1) {
                continue;
            }
            let possibility = (Math.pow(pheromone[currentCity][nextCity], alpha) * 
                               Math.pow(1 / Distance(currentCity, nextCity), beta) / sum);

            if (possibility > maximalPossibility) {
                maximalPossibility = possibility, city = nextCity;
            }
        }

        return city;
    };
    
    this.CalculateDown = function(currentCity) {
        let sum = 0.0;
        for (let nextCity = 0; nextCity < cityNumber; nextCity++) {
            if (this.hasVisitedCity.indexOf(nextCity) !== -1) {
                continue;
            }
            
            sum += (Math.pow(pheromone[currentCity][nextCity], alpha) * 
                    Math.pow(1 / Distance(currentCity, nextCity), beta));
        }

        return sum;
    };

    this.Update = function(currentCity, nextCity) {
        this.path.push(nextCity);
        this.hasVisitedCity.push(nextCity);
        this.sumOfDistance += Distance(currentCity, nextCity);
    }
};

function Distance(currentCity, nextCity) {
    // console.log(currentCity + ', ' + nextCity);
    let dist = Math.pow(map[currentCity][0] - map[nextCity][0], 2) + 
               Math.pow(map[currentCity][1] - map[nextCity][1], 2);
    return Math.sqrt(dist);
}

function Initial() {
    alpha = 2.0, beta = 2.0, rho = 0.45, Q = 40.0;
    antNumber = 30, maxIterations = 50, antGroup = [];
    cityNumber = 30;
    for (let i = 0; i < cityNumber; i++) {
        let city = [Math.random() * 1000, Math.random() * 1000];
        map.push(city);
    }
    // console.log(cityNumber);
    // 二维信息素矩阵
    pheromone = new Array(map.length);
    for (let i = 0; i < cityNumber; i++) {
        pheromone[i] = new Array(map.length);
        for (let j = 0; j < map.length; j++)
            pheromone[i][j] = 0.0;
    }
    
    
    let sumLength = 0.0;
    for (let i = 0; i < map.length - 1; i++) {
        sumLength += Distance(i, i + 1);
    }
    sumLength += Distance(map.length - 1, 0);

    for (let i = 0; i < map.length - 1; i++) {
        pheromone[i][i + 1] += (antNumber / sumLength);
        pheromone[i + 1][i] += (antNumber / sumLength);
    }
    pheromone[map.length - 1][0] += (antNumber / sumLength);
    pheromone[0][map.length - 1] += (antNumber / sumLength);
};

function UpdatePheromone() {
    let deltaPheromone = new Array(cityNumber);
    for (let i = 0; i < cityNumber; i++) {
        deltaPheromone[i] = new Array(cityNumber);
        for (let j = 0; j < cityNumber; j++) {
            deltaPheromone[i][j] = 0.0;
        }
    }

    for (let i = 0; i < antGroup.length; i++) {
        let ant = antGroup[i];
        for (let currentCity = ant.path[0]; currentCity < ant.length - 1; currentCity++) {
            let nextCity = ant.path[currentCity + 1];
            deltaPheromone[currentCity][nextCity] += (Q / ant.sumOfDistance);
            deltaPheromone[nextCity][currentCity] += (Q / ant.sumOfDistance);
        }
    }

    for (let i = 0; i < cityNumber; i++) {
        for (let j = 0; j < cityNumber; j++) {
            pheromone[i][j] *= (1 - rho);
            pheromone[i][j] += deltaPheromone[i][j];
        }
    }
}


function SetAnt() {
    antGroup = [];
    for (let i = 0; i < antNumber; i++) {
        let randomCity = Math.floor(Math.random() * cityNumber);
        antGroup.push(new Ant(randomCity));
    }
}

function TSP() {
    let minimalDistance = Math.pow(2, 30);
    Initial();
    for (let i = 0; i < maxIterations; i++) {
        SetAnt();
        for (let j = 0; j < antNumber; j++) {
            antGroup[j].Travel();
            minimalDistance = Math.min(minimalDistance, antGroup[j].sumOfDistance);
        }
        UpdatePheromone();
        console.log(minimalDistance);
    }
    console.log(minimalDistance);
}

TSP();