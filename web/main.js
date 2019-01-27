// requires
import Engine from "./engine.js";
//

const main = () => {
    const engine = new Engine(600,600,1000,1000);
    engine.initialize();
    engine.runLoop()
};

main ();


