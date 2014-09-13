#ifndef __DRERENDERQUEUEGROUP_H__
#define __DRERENDERQUEUEGROUP_H__

/// scene manager
#include "DreSceneManagerDeclaration.h"
#include "DreRenderable.h"

/// config
#include "DreMemoryAllocatorConfig.h"

namespace dream
{
	/** \addtogroup Core
	*  @{
	*/

	/** \addtogroup RenderSystem
	*  @{
	*/

	/** 绑定单个 renderable 与单个 pass 的结构体
	* @note
	*	renderable 与 pass之间的关系是多对多
	*/
	struct RenderablePass
	{
		RenderablePtr renderable;
		PassPtr pass;

		RenderablePass(RenderablePtr rend, PassPtr p) :renderable(rend), pass(p) {}
	};


	/** 访问者模式，用于遍历 QueuedRenderableCollection. */
	class DRE_EXPORT_CLASS QueuedRenderableVisitor
	{
	public:
		QueuedRenderableVisitor() {}
		virtual ~QueuedRenderableVisitor() {}

		/* 当使用 OM_PASS_GROUP以外 方式遍历 QueuedRenderableCollection 时调用该方法
		* @param
		*	p				Pass				一次渲染过程
		* @param
		*	renderList		RenderableList		可渲染对象链表
		* @remarks
		*	由于排序时仍然把使用相同 Pass 的 Renderable 放在一起，
		*	因此最好检查一下前面一个 Pass，是否与当前 Pass 相同，
		*	减少 DrawCall
		*/
		virtual void visit(RenderablePass* rp) = 0;

		/* 当使用 OM_PASS_GROUP 方式遍历 QueuedRenderableCollection 时调用该方法
		* @param
		*	p				Pass				一次渲染过程
		* @param
		*	renderList		RenderableList		可渲染对象链表
		* @remarks
		*	由于使用 OM_PASS_GROUP 方式 Renderable 会按照 对应的 pass 进行组合，
		*	因此 renderList 中的所有元素均使用 p 作为 Pass
		*/
		virtual bool visit(Pass* p, const RenderableList& renderList) = 0;
	};

	/** 最底层的 Renderable 集合
	@remarks
	To iterate over items in this collection, you must call
	the accept method and supply a QueuedRenderableVisitor.
	The order of the iteration, and whether that iteration is
	over a RenderablePass list or a 2-level grouped list which
	causes a visit call at the Pass level, and a call for each
	Renderable underneath.
	*/
	class DRE_EXPORT_CLASS QueuedRenderableCollection
	{
	public:
		/** 标志当前 RenderableCollection 应该如何被组织
		* @note
		*	OM_SORT_ASCENDING 与 OM_SORT_DESCENDING 的排序方式相同只是顺序相反
		@remarks
		This affects the internal placement of the items added to this collection;
		if only one type of sorting / grouping is to be required, then renderables
		can be stored only once, whilst if multiple types are going to be needed
		then internally there will be multiple organisations. Changing the organisation
		needs to be done when the collection is empty.
		*/
		enum OrganisationMode : u8
		{
			/// 按照 pass 分组，绑定的 pass 相同的 Renderable 会靠在一起遍历
			OM_PASS_GROUP = 1,
			/// 按照与相机之间的距离排序，越远顺序越前
			OM_SORT_DESCENDING = 2,
			/// 按照与相机之间的距离排序，越近顺序越前
			OM_SORT_ASCENDING = 6
		};

	protected:
		/// 按 pass 排序 QueuedRenderableCollection 的比较器 
		struct DRE_EXPORT_CLASS PassGroupLess
		{
			bool  operator()(const PassPtr a, const PassPtr b) const;
		};

		/// 按相机距离排序 QueuedRenderableCollection 的比较器 
		struct DRE_EXPORT_CLASS DepthSortDescendingLess
		{
			const Camera* camera;

			DepthSortDescendingLess(const Camera* cam)
				: camera(cam)
			{
				// 留空
			}

			bool operator()(const RenderablePass& a, const RenderablePass& b) const;
		};

		/** Vector of RenderablePass objects, this is built on the assumption that
		vectors only ever increase in size, so even if we do clear() the memory stays
		allocated, ie fast */
		typedef vector<RenderablePass>			RenderablePassList;
		typedef vector<RenderablePtr>			RenderableList;
		/** 默认按照 OM_PASS_GROUP 方式组织 */
		typedef map<PassPtr, RenderableList, PassGroupLess> PassGroupRenderableMap;

		/// 按照 Pass 分组组织的集合
		PassGroupRenderableMap				mGrouped;
		/// 根据相机排序后集合
		RenderablePassList					mSortedDescending;

		/// 接受访问器已 OM_PASS_GROUP 的方式遍历集合
		void AcceptVisitorGrouped(QueuedRenderableVisitor* visitor) const;
		/// 接受访问器已 OM_SORT_DESCENDING 的方式遍历集合
		void AcceptVisitorDescending(QueuedRenderableVisitor* visitor) const;
		/// 接受访问器已 OM_SORT_ASCENDING 的方式遍历集合
		void AcceptVisitorAscending(QueuedRenderableVisitor* visitor) const;

	public:
		/// 默认构造函数
		QueuedRenderableCollection();
		~QueuedRenderableCollection()
		{
			// 清空集合
			this->Clear();
		}

		/// 清空集合
		void Clear(void);

		/** 添加一个 Renderable 与 pass 绑定
		* @param
		*	pass		Pass			渲染过程
		* @param	
		*	rend		Renderable		渲染对象
		*/
		void AddRenderable(Pass* pass, Renderable* rend);

		/** 根据给定的相机进行排序
		* @param 
		*	cam		Camera			用于排序的相机
		*/
		void Sort(const Camera* cam);

		/** 接受访问器遍历所有 Renderable
		* @param
		*	visitor		QueuedRenderableVisitor		访问器指针
		* @param
		*	om			OrganisationMode			遍历模式
		*/
		void AcceptVisitor(QueuedRenderableVisitor* visitor, OrganisationMode om) const;

		/** 合并两个 QueuedRenderableCollection 集合 */
		void Merge(const QueuedRenderableCollection& rhs);
	};

	/** 根据 renderable 的 LayerID 进行分组的集合
	@remarks
	This class simply groups renderables for rendering. All the
	renderables contained in this class are destined for the same
	RenderQueueGroup (coarse groupings like those between the main
	scene and overlays) and have the same priority (fine groupings
	for detailed overlap control).
	@par
	This class can order solid renderables by a number of criteria;
	it can optimise them into groups based on pass to reduce render
	state changes, or can sort them by ascending or descending view
	depth. Transparent objects are always ordered by descending depth.
	@par
	To iterate over items in the collections held by this object
	you should retrieve the collection in use (e.g. solids, solids with
	no shadows, transparents) and use the accept() method, providing
	a class implementing QueuedRenderableVisitor.

	*/
	class DRE_EXPORT_CLASS RenderLayerGroup
	{
	protected:
		RenderQueueGroup* mParent;
		bool mSplitPassesByLightingType;
		bool mSplitNoShadowPasses;
		bool mShadowCastersNotReceivers;

		/// Solid pass list, used when no shadows, modulative shadows, or ambient passes for additive
		QueuedRenderableCollection mSolidsBasic;
		/// Solid per-light pass list, used with additive shadows
		QueuedRenderableCollection mSolidsDiffuseSpecular;
		/// Solid decal (texture) pass list, used with additive shadows
		QueuedRenderableCollection mSolidsDecal;
		/// Solid pass list, used when shadows are enabled but shadow receive is turned off for these passes
		QueuedRenderableCollection mSolidsNoShadowReceive;

		/** 添加一个 renderable 到集合
		* @param
		*	pTech				Technique*		渲染使用的Technique
		* @param
		*	rend				RenderablePtr	渲染对象
		* @param
		*	toNoShodowMap		bool			是否使用光照贴图，true为使用光照贴图
		*/
		void AddSolidRenderable(TechniquePtr pTech, RenderablePtr rend, bool toNoShadowMap);

		/** 添加一个 renderable 到集合中，按照光照类型划分 renderable 对象的归属
		*@param
		*	pTech				Technique*		渲染使用的Technique
		* @param
		*	rend				RenderablePtr	渲染对象
		*/
		void AddSolidRenderableSplitByLightType(TechniquePtr pTech, Renderable* rend);

	public:
		RenderLayerGroup(RenderQueueGroup* parent);

		~RenderLayerGroup() { }

		/** Get the collection of basic solids currently queued, this includes
		all solids when there are no shadows, or all solids which have shadow
		receiving enabled when using modulative shadows, or all ambient passes
		of solids which have shadow receive enabled for additive shadows. */
		const QueuedRenderableCollection& GetSolidsBasic(void) const
		{
			return mSolidsBasic;
		}
		/** Get the collection of solids currently queued per light (only applicable in
		additive shadow modes). */
		const QueuedRenderableCollection& GetSolidsDiffuseSpecular(void) const
		{
			return mSolidsDiffuseSpecular;
		}
		/** Get the collection of solids currently queued for decal passes (only
		applicable in additive shadow modes). */
		const QueuedRenderableCollection& GetSolidsDecal(void) const
		{
			return mSolidsDecal;
		}
		/** Get the collection of solids for which shadow receipt is disabled (only
		applicable when shadows are enabled). */
		const QueuedRenderableCollection& GetSolidsNoShadowReceive(void) const
		{
			return mSolidsNoShadowReceive;
		}

		/** 添加一个 renderable 到集合中 */
		void AddRenderable(RenderablePtr pRend, TechniquePtr pTech);

		/** 清空集合，会释放为收集 renderable 产生的空间 */
		void Clear(void);

		/** 设置集合中所有 renderable 是否可以根据光照类型进行分组 */
		void SetSplitPassesByLightingType(bool split)
		{
			mSplitPassesByLightingType = split;
		}

		/** 设置集合中所有 renderable 是否可以接收阴影 */
		void SetSplitNoShadowPasses(bool split)
		{
			mSplitNoShadowPasses = split;
		}

		/** 设置集合中具有 ShadowCaster 属性的 renderable 是否可以接收阴影 */
		void setShadowCastersCannotBeReceivers(bool ind)
		{
			mShadowCastersNotReceivers = ind;
		}

		/** 合并 RenderLayerGroup */
		void merge(const RenderLayerGroup* rhs);
	};

	/** 根据与 renderable 绑定的 Technique 指定的 Queue（渲染顺序）进行分组的集合 */
	class RenderQueueGroup : public std::enable_shared_from_this<RenderQueueGroup>
	{
	public:
		typedef map<LayerID, RenderLayerGroup*, std::less<LayerID> >		LayerMap;
		typedef LayerMap::iterator											GroupIte;
		typedef LayerMap::const_iterator									GroupConstIte;

	protected:
		RenderQueuePtr mParent;

		/// 根据 renderable 的LayerID进行分组
		LayerMap mLayerGroups;
	public:
		RenderQueueGroup(RenderQueue* parent)
			: mParent(parent)
		{
			// 留空
		}

		~RenderQueueGroup() {
			// destroy contents now
			GroupIte ite;
			for (ite = mLayerGroups.begin(); ite != mLayerGroups.end(); ++ite)
			{
				DREAM_DELETE ite->second;
			}
		}

		GroupIte begin(void) { return mLayerGroups.begin(); }
		GroupConstIte begin(void) const { return mLayerGroups.begin(); }

		GroupIte end(void) { return mLayerGroups.end(); }
		GroupConstIte end(void) const { return mLayerGroups.end(); }

		/** 添加一个 renderable 到集合中 */
		void AddRenderable(RenderablePtr pRend, TechniquePtr pTech)
		{
			GroupIte ite = mLayerGroups.find(pRend->GetLayerID());
			RenderLayerGroup* pLayerGroup;

			if (ite == mLayerGroups.end())
			{
				pLayerGroup = DREAM_NEW RenderLayerGroup(this);
				mLayerGroups.insert(LayerMap::value_type(pRend->GetLayerID(), pLayerGroup));
			}
			else
			{
				pLayerGroup = ite->second;
			}

			// Add
			pLayerGroup->AddRenderable(pRend, pTech);

		}

		/** 清空集合
		* @param 
		*	destroy			bool		如果 false 则保留分配的mLayerGroups
		*/
		void Clear(bool destroy = false)
		{
			GroupIte i, iend;
			iend = mLayerGroups.end();
			for (i = mLayerGroups.begin(); i != iend; ++i)
			{
				if (destroy)
					DREAM_DELETE i->second;
				else
					i->second->Clear();
			}

			if (destroy)
				mLayerGroups.clear();

		}

		/** Merge group of renderables.
		*/
		void merge(const RenderQueueGroup* rhs)
		{
			GroupConstIte srcIte = rhs->begin();

			for (; srcIte != rhs->end(); ++srcIte)
			{
				GroupConstIte dstIte = this->mLayerGroups.find(srcIte->first);
				if (dstIte == this->mLayerGroups.end())
				{
					mLayerGroups.insert(LayerMap::value_type(srcIte->first, srcIte->second));
				}
				else
				{
					dstIte->second->merge(srcIte->second);
				}
			}
		}
	};	// end class RenderGroup

}	// end namespace dream

#endif // !__DRERENDERGROUP_H__
