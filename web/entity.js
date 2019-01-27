//const ranN = num => Math.floor(Math.random() * num); //return random number from 0-num

class Entity {
	constructor(h, w, x, y, id) {
		this.h = h;
		this.w = w;
		this.pos = { x: x, y: y };
		this.disp = { x: null, y: null };
        
        this.mult={x:1,y:1};
        
        this.id = id;
        
	}
	update(user,mult) {
        this.pos.x += ranN(3)-1;
        this.pos.y += ranN(3)-1;

        this.mult.x = mult.x;
        this.mult.y = mult.y;

        this.disp.x=this.pos.x-user.x+user.dispX/mult.x;
        this.disp.y=this.pos.y-user.y+user.dispY/mult.y;


    }
	render(ctx) {
        ctx.fillRect(this.disp.x*this.mult.x,this.disp.y*this.mult.y,this.w*this.mult.x,this.h*this.mult.y)
    }
}

export default Entity;

const ranN = (num) => Math.floor(Math.random() * num); //return random number from 0-num
