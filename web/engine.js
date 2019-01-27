import Viewport from "./viewport.js";
import Entity from "./entity.js";
import Quadtree from "./quadtree.js";

const ranN = num => Math.floor(Math.random() * num); //return random number from 0-num

class Engine {
	constructor(canvasHeight, canvasWidth, mapHeight, mapWidth) {
		this.canvas = document.createElement("canvas");
		this.canvas.id = "canvas";
		this.canvas.width = canvasHeight;
		this.canvas.height = canvasWidth;
		this.ctx = this.canvas.getContext("2d");

		this.map = { height: mapHeight, width: mapWidth };

		this.runLoop = this.runLoop.bind(this);
		this.mapKeys = {};
		this.mapMouse = {};

		this.user = { x: 500, y: 500, dispX: 500, dispY: 500 };
		this.mult = { x: 1, y: 1 };

		this.viewport = null;
		this.entities = new Map();
		this.entityDeadPool = [];

		this.quadtree = null;
	}
	initialize() {
		let mainContainer = document.getElementById("container");
		mainContainer.appendChild(this.canvas);

		//init the viewport
		this.viewport = new Viewport(
			this.canvas.height,
			this.canvas.width,
			this.map.height,
			this.map.width
		);

		//init the entities
		for (let i = 0; i < 800; i++) {
			let entity = new Entity(
				10,
				10,
				ranN(800) + 100,
				ranN(800) + 100,
				`entity${i}`
			);
			this.entities.set(entity.id, entity);
		}
		this.quadtree = new Quadtree(
			{ x: 0, y: 0, width: this.map.width, height: this.map.height },
			5,
			20
		);

		for (let entity of this.entities.values()) {
			if (entity.isAlive) {
				this.quadtree.insert(entity);
			}
		}
	}

	pollEvents() {
		onmousedown = onmouseup = onmousemove = onwheel = e => {
			e = e;
			// LEFT CLICK ONLY
			if (e.type === "mouseup" && e.button === 0) {
				this.mapMouse["pressed"] = false;
			} else if (e.type === "mousedown" && e.button === 0) {
				this.mapMouse["pressed"] = true;
				this.mapMouse["initPos"] = {
					x: e.clientX / this.mult.x + this.user.x,
					y: e.clientY / this.mult.y + this.user.y
				};
			}
			if (e.type === "wheel") {
				if (e.deltaY < 0) {
					let zoom = "in";
					this.camera(zoom);
					// viewport zoomin
				} else if (e.deltaY > 0) {
					let zoom = "out";
					this.camera(zoom);
					//viewport zoomout
				}
			}
			this.mapMouse["x"] = e.clientX;
			this.mapMouse["y"] = e.clientY;
		};
		onkeydown = onkeyup = e => {
			e = e;
			this.mapKeys[e.keyCode] = e.type == "keydown";
		};
	}

	camera(zoom) {
		if (this.mapMouse.pressed) {
			let x = Math.round(
				this.mapMouse.initPos.x - this.mapMouse.x / this.mult.x
			);
			let y = Math.round(
				this.mapMouse.initPos.y - this.mapMouse.y / this.mult.y
			);

			//		console.log(x);
			this.user.x = x;
			this.user.y = y;
		}
		//	console.log(zoom);
		switch (zoom) {
			case "in":
				{
					this.mult.x *= 1.1;
					this.mult.y *= 1.1;
				}
				break;
			case "out":
				{
					this.mult.x *= 0.9;
					this.mult.y *= 0.9;
				}
				break;
		}
	}
	// update all entities and views
	update(dt) {
		//listen for user and camera controls
		this.pollEvents();
		this.camera();

		this.quadtree.clear();

		for (let entity of this.entities.values()) {
			if (entity.isAlive) {
				entity.isColliding = false;

				entity.update(this.user, this.mult);
				this.quadtree.insert(entity);
			}
		}
		//	let timeNow = Date.now()

		for (let entity of this.entities.values()) {
			if (entity.isAlive) {
				let entityArr = this.quadtree.retrieve(entity);
				this.collision(entity, entityArr);
			}
		} //	console.log(Date.now()-timeNow)
	}
	// update tree
	collision(entity, entityArr) {
		let lens = entityArr.length;
		if (lens > 1) {
			for (let i = lens - 1; i >= 0; i--) {
				let target = entityArr[i];
				if (entity.id != target.id) {
			//		let dis2 = Math.pow(entity.x-target.x,2)+Math.pow(entity.y-target.y,2);
			//		let size2 = entity.width*entity.width;
			//		console.log(dis2)
					if (
					//	dis2<size2
						entity.x >= target.x &&
						entity.x <= target.x + target.width &&
						entity.y >= target.y &&
						entity.y <= target.y + target.height
					) {
						target.isColliding = true;
						entity.isColliding = true;
						//do things here
					} else {
						//		entity.isColliding = false;
						//		target.isColliding = false;
					}
				}
			}
		}
	}

	//render all entities and refreshes
	render(dt) {
		//	let timeNow = Date.now();

		this.ctx.fillStyle = "rgb(0, 71, 0)";
		this.ctx.fillRect(0, 0, this.canvas.width, this.canvas.height);
		this.ctx.beginPath();
		//render entities

		this.ctx.fillStyle = "rgb(210, 111, 20)";

		for (let entity of this.entities.values()) {
			//        console.log(entity)
			if (entity.isAlive) {
				entity.render(this.ctx);
			}
		}
		//		this.ctx.fillRect(this.user.dispX, this.user.dispY, 20, 20);    USER POS
		this.ctx.stroke();

		this.ctx.closePath();

		//	console.log(Date.now()-timeNow);
	}

	runLoop() {
		//get time per frame
		let lastTime = Date.now();
		let now = Date.now();
		let dt = (now - lastTime) / 1000;

		this.update(dt);
		this.render(dt);
		window.requestAnimationFrame(this.runLoop);
		//		console.log(this.map);
		//reset lasttime to now
		lastTime = now;
		// clear quadtree;
	}
}

export default Engine;
