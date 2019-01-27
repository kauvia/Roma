// requires
import Engine from "./engine.js";
//

const main = () => {
    const engine = new Engine(600,600,600,600);
    engine.initialize();
    engine.runLoop()
};

main ();


