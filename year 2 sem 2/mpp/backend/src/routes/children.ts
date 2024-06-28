import express from 'express';
import * as ChildrenController from '../controllers/children';

const router =  express.Router();

router.get("/", ChildrenController.getChildren);
router.post("/", ChildrenController.createChild);
router.get("/parents", ChildrenController.getParents);
router.get("/parent/:parentId", ChildrenController.getChildrenByParentID);
router.get("/:childId", ChildrenController.getChild);
router.put("/:childId", ChildrenController.updateChild);
router.get("/parents", ChildrenController.getParents);

export default router