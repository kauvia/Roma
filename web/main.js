// requires
import Engine from "./engine.js";
//

const main = () => {
    const engine = new Engine(600,600,3000,3000);
    engine.initialize();
    engine.runLoop()
};

main ();


