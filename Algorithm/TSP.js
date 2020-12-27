const canvas = document.querySelector(".myCanvas");
const width = canvas.width = window.innerWidth;
const height = canvas.height = window.innerHeight;

const ctx = canvas.getContext("2d");
ctx.strokeStyle = "rgb(0, 0, 0)";
ctx.lineWidth = 1;

let alpha, beta, rho, Q, antNumber, maxIterations, antGroup, pheromone, cityNumber;
// 信息素因子, 启发函数因子, 信息挥发因子, 信息素常量, 蚂蚁数量, 最大迭代次数, 蚂蚁群, 信息素矩阵
const mapX = [178,272,176,171,650,499,267,703,408,437,491,74,532,
    416,626,42,271,359,163,508,229,576,147,560,35,714,
    757,517,64,314,675,690,391,628,87,240,705,699,258,
    428];

const mapY = [170,395,198,151,242,556,57,401,305,421,267,105,525,
    381,244,330,395,169,141,380,153,442,528,329,232,48,
    498,265,343,120,165,50,433,63,491,275,348,222,288,
    490];

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
            // console.log("目前在" + currentCity + ", 距离为" + this.sumOfDistance);
        }
        this.GoBackStart();   
        // console.log(this.sumOfDistance);
        // console.log("next"); 
    };

    this.GoBackStart = function() {
        this.sumOfDistance += Distance(this.path[this.path.length - 1], this.path[0]);
        this.path.push(this.path[0]);
    }

    this.ChooseNextCity = function(currentCity, sum) {
        // 轮盘赌法
        let city, maximalPossibility = 0.0, sumPossibility = 0.0;
        let allowedCity = [];
        for (let nextCity = 0; nextCity < cityNumber; nextCity++) {
            if (this.hasVisitedCity.indexOf(nextCity) !== -1) {
                continue;
            }
            let possibility = (Math.pow(pheromone[currentCity][nextCity], alpha) * 
                               Math.pow(1 / Distance(currentCity, nextCity), beta) / sum);
            sumPossibility += possibility;
            allowedCity.push([nextCity, possibility]);
        }

        allowedCity.forEach((el) => {
            el[1] = el[1] / sumPossibility;
        });
        
        allowedCity[0].push(allowedCity[0][1]);
        for (let i = 1; i < allowedCity.length; i++) {
            let accumlatedPossibility = allowedCity[i - 1][2] + allowedCity[i][1];
            allowedCity[i].push(accumlatedPossibility);
        }
        
        let randomNumber = Math.random();
        for (let i = 1; i < allowedCity.length; i++) {
            if (randomNumber <= allowedCity[i][2]) {
                city = i;
                break;
            }
        }
        // console.log("city: " + city);
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

        ctx.beginPath();

        ctx.moveTo(mapX[currentCity], mapY[currentCity]);
        ctx.lineTo(mapX[nextCity], mapY[nextCity]);
        ctx.closePath();
        ctx.stroke();
    }
};

function Distance(currentCity, nextCity) {
    let dist = Math.pow(mapX[currentCity] - mapX[nextCity], 2) + 
               Math.pow(mapY[currentCity] - mapY[nextCity], 2);
    return Math.sqrt(dist);
}

function Initial() {
    alpha = 3.0, beta = 3.0, rho = 0.65, Q = 100.0;
    antNumber = 20, maxIterations = 150, antGroup = [];
    cityNumber = mapX.length;

    // console.log(cityNumber);
    // 二维信息素矩阵
    pheromone = new Array(cityNumber);
    for (let i = 0; i < cityNumber; i++) {
        pheromone[i] = new Array(cityNumber);
        for (let j = 0; j < cityNumber; j++) {
            pheromone[i][j] = 1.0;
        }
    }
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


function Reset() {
    antGroup = [];
    for (let i = 0; i < antNumber; i++) {
        let randomCity = Math.floor(Math.random() * cityNumber);
        antGroup.push(new Ant(randomCity));
    }

}

function ClearCanvas() {
    ctx.clearRect(0, 0, canvas.width, canvas.height);
} 

function loop() {
    let minimalDistance = Math.pow(2, 30);
    Reset();
    for (let j = 0; j < antNumber; j++) {
        ClearCanvas();
        antGroup[j].Travel();
        // antGroup[j].Travel();
        minimalDistance = Math.min(minimalDistance, antGroup[j].sumOfDistance);
    }
    UpdatePheromone();
    // console.log("第" + iterations + "次迭代, 最短路径长度为: " + minimalDistance);    
    // if (iterations++ < maxIterations)
        requestAnimationFrame(loop);
}

function TSP() {
    let minimalDistance = Math.pow(2, 30);
    Initial();
    // let iterations = 0;
    loop();

    // for (let i = 1; i <= maxIterations; i++) {
    //     Reset();
    //     window.requestAnimationFrame(run());
    //     // console.log("next");
    //     UpdatePheromone();
    //     console.log("第" + i + "次迭代, 最短路径长度为: " + minimalDistance);
    // }
    // console.log(minimalDistance);
}

TSP();