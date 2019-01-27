//const ranN = num => Math.floor(Math.random() * num); //return random number from 0-num

class Entity {
	constructor(h, w, x, y, id) {
		this.id = id;

		this.height = h;
		this.width = w;
		this.x = x;
		this.y = y;
		this.disp = { x: null, y: null };
		this.mult = { x: 1, y: 1 };

		this.isAlive = true;
		this.isColliding = false;
		this.energy = ranN(1000);
	}
	update(user, mult) {
		this.x += (ranN(3) - 1) / 8;
		this.y += (ranN(3) - 1) / 8;

		this.mult.x = mult.x;
		this.mult.y = mult.y;

		this.disp.x = this.x - user.x + user.dispX / mult.x;
		this.disp.y = this.y - user.y + user.dispY / mult.y;
	}
	render(ctx) {
		this.isColliding
			? (ctx.fillStyle = "rgb(255,0,255")
			: (ctx.fillStyle = "rgb(210,111,20");
		ctx.fillRect(
			this.disp.x * this.mult.x,
			this.disp.y * this.mult.y,
			this.width * this.mult.x,
			this.height * this.mult.y
		);
	}
}

export default Entity;

const ranN = num => Math.floor(Math.random() * num); //return random number from 0-num
