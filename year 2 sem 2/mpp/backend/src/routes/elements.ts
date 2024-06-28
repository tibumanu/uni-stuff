
import express from "express";
import * as ElementsController from "../controllers/elements";

const router = express.Router();

router.get("/chartdata", ElementsController.getChartData);
router.get("/sort", ElementsController.getSortedElements);
router.get("/page", ElementsController.getGamesByPageServer);
//router.get("/totalelements", ElementsController.getTotalElements);
router.get("/totalelement/:elementId", ElementsController.getTotalElement);
router.get("/", ElementsController.getElements);

router.get("/:elementId", ElementsController.getElement);

router.post("/", ElementsController.createElement);

router.patch("/:elementId", ElementsController.updateElement);

router.delete("/:elementId", ElementsController.deleteElement);

router.get("/filter/:smth", ElementsController.getFilteredElements);



export default router;