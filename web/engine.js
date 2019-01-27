class Engine {
    constructor(canvasHeight,canvasWidth, mapHeight,mapWidth){
        this.mainContainer = document.getElementById('container');
        this.canvas = document.createElement('canvas');
        this.mainContainer.appendChild(this.canvas);

        this.canvas.id = "main-canvas";

        this.canvas.width = canvasHeight;
        this.canvas.height = canvasWidth;
        this.ctx = this.canvas.getContext('2d');

        this.runLoop = this.runLoop.bind(this);

        this.lastTime = Date.now();
        this.now = Date.now();
        this.dt = (this.now-this.lastTime)/1000;
    }
	initialize() {
        // draw canvas boundary
        this.ctx.rect(0,0,this.canvas.width,this.canvas.height);
        this.ctx.stroke()
        console.log(this.rAF)
    }
    
    render(dt){

    }

    update(dt){

    }


    runLoop(){
        //get time per frame
        this.now = Date.now();
        this.dt =  (this.now-this.lastTime)/1000;

        this.update(this.dt);
        this.render(this.dt);
        window.requestAnimationFrame(this.runLoop);

        //reset lasttime to now
        this.lastTime = this.now;
    }
}

export default Engine;
