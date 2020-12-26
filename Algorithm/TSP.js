let alpha, beta, rho, Q, antNumber, maxIterations, antGroup, pheromone, cityNumber;
// 信息素因子, 启发函数因子, 信息挥发因子, 信息素常量, 蚂蚁数量, 最大迭代次数, 蚂蚁群
const map = [[11.0, 12.0], [144.1, 2.1], [70.8, 121.9]];

class Ant {
    constructor(startCity) {
        this.path.push(startCity);
        this.hasVisitedCity.push(startCity);
    }

    path = [];
    hasVisitedCity = [];
    sumOfDistance = 0.0;

    Travel() {
        for (let i = 0; i < cityNumber - 1; i++) {
            let currentCity = this.path[this.path.length - 1];
            let sum = this.CalculateDown(currentCity);
            let nextCity = this.ChooseNextCity(sum);
            Update(nextCity);    
        }
    }

    ChooseNextCity(sum) {
        // 从剩下的城市里挑一个最可能去的
        let city = currentCity, maximalPossibility = 0.0;
        for (let nextCity = 0; nextCity < cityNumber; nextCity++) {
            if (this.hasVisitedCity.find(nextCity) === undefined) {
                continue;
            }
            let possibility = (Math.pow(pheromone[currentCity][nextCity], alpha) * 
                               Math.pow(Distance(currentCity, nextCity), beta) / sum);

            if (possibility > maximalPossibility) {
                maximalPossibility = possibility, city = nextCity;
            }
        }

        return city;
    }

    CalculateDown(currentCity) {
        let sum = 0.0, 
        for (let nextCity = 0; nextCity < cityNumber; nextCity++) {
            if (this.hasVisitedCity.find(nextCity) === undefined) {
                continue;
            }
            sum += (Math.pow(pheromone[currentCity][nextCity], alpha) * 
                    Math.pow(Distance(currentCity, nextCity), beta));
        }
        return sum;
    }

    Distance(currentCity, nextCity) {
        let dist = Math.pow(map[currentCity][0] - map[nextCity][0]) + 
                   Math.pow(map[currentCity][1] - map[nextCity][1]);
        return Math.floor(Math.sqrt(dist));
    }

    Update(nextCity) {
        this.path.push(nextCity);
        this.hasVisitedCity.push(nextCity);
    }
}

function Initial() {
    alpha = 2.0, beta = 1.0, rho = 0.3, Q = 40.0;
    antNumber = 5, maxIterations = 50, antGroup = [], cityNumber = map.length;
    for (let i = 0; i < antNumber; i++) {
        let randomCity = Math.floor(Math.random() * cityNumber);
        antGroup.push(new Ant(randomCity));
    }
};

function UpdatePheromone() {
    
}

function TSP() {
    Initial();
    for (let i = 0; i < maxIterations; i++) {
        for (let j = 0; j < antNumber; j++) {
            antGroup[j].Travel();
        }
        UpdatePheromone();
    }
}